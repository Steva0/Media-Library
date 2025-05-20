#include "Ebook.h"

namespace media {

Ebook::Ebook(const std::string& title, int publicationYear, const std::string& language,
             bool favorite, const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
             const std::string& author, const std::string& publisher,
             unsigned int pages, const std::string& series, const std::string& isbn,
             unsigned int fileSizeBytes, bool drm)
    : Novel(title, publicationYear, language, favorite, genres, imagePath, notes,
            author, publisher, pages, series, isbn),
      fileSizeBytes_(fileSizeBytes), drm_(drm) {}

bool Ebook::operator==(const Media& other) const {
    const Ebook* otherEbook = dynamic_cast<const Ebook*>(&other);
    if (otherEbook) {
        return Novel::operator==(*otherEbook) && fileSizeBytes_ == otherEbook->fileSizeBytes_ &&
               drm_ == otherEbook->drm_;
    }
    return false;
}   

unsigned int Ebook::getFileSizeBytes() const {
    return fileSizeBytes_;
}

bool Ebook::hasDrm() const {
    return drm_;
}

void Ebook::setFileSizeBytes(unsigned int size) {
    fileSizeBytes_ = size;
}

void Ebook::setDrm(bool drm) {
    drm_ = drm;
}

std::vector<std::shared_ptr<Media>> Ebook::filter(const std::vector<std::shared_ptr<Ebook>>& input) const {
    std::vector<std::shared_ptr<Media>> result;

    // Riutilizza filtro base di Novel (che include filtro di Media)
    std::vector<std::shared_ptr<Novel>> novels(input.begin(), input.end());
    std::vector<std::shared_ptr<Media>> filteredNovels = Novel::filter(novels);

    // Filtro specifico Ebook
    for (const auto& novelPtr : filteredNovels) {
        auto ebookPtr = std::dynamic_pointer_cast<Ebook>(novelPtr);
        if (!ebookPtr) continue;

        bool match = true;

        // File size
        if (fileSizeBytes_ > 0 && ebookPtr->getFileSizeBytes() != fileSizeBytes_)
            match = false;

        // DRM
        if (drm_ && ebookPtr->hasDrm() != drm_)
            match = false;

        if (match)
            result.push_back(ebookPtr);
    }

    return result;
}


}