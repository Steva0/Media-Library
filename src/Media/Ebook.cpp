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

std::unique_ptr<Media> Ebook::clone() const {
    return std::make_unique<Ebook>(*this);
}

bool Ebook::filter(const Media& input) const {
    // Riutilizzo filtro base di Novel
    if (!Novel::filter(input))
        return false;
    // Cast to Ebook to access Ebook-specific members
    const Ebook* ebookPtr = dynamic_cast<const Ebook*>(&input);
    if (!ebookPtr)
        return false;

    // File size filter
    if (fileSizeBytes_ > 0 && ebookPtr->getFileSizeBytes() != fileSizeBytes_)
        return false;

    // DRM filter
    if (drm_ && ebookPtr->hasDrm() != drm_)
        return false;

    return true;
}

}