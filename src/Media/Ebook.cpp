#include "Ebook.h"

namespace media {

Ebook::Ebook(const std::string& title, int publicationYear, const std::string& language,
             bool favorite, const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
             const std::string& author, const std::string& publisher,
             int pages, const std::string& series, const std::string& isbn,
             int fileSizeBytes, bool drm)
    : Novel(title, publicationYear, language, favorite, genres, imagePath, notes,
            author, publisher, pages, series, isbn),
      fileSizeBytes_(fileSizeBytes > 0 ? fileSizeBytes : std::numeric_limits<int>::min()), drm_(drm) {}

bool Ebook::operator==(const Media& other) const {
    const Ebook* otherEbook = dynamic_cast<const Ebook*>(&other);
    if (otherEbook) {
        return Novel::operator==(*otherEbook) && fileSizeBytes_ == otherEbook->fileSizeBytes_ &&
               drm_ == otherEbook->drm_;
    }
    return false;
}   

int Ebook::getFileSizeBytes() const {
    return fileSizeBytes_;
}

bool Ebook::hasDrm() const {
    return drm_;
}

void Ebook::setFileSizeBytes(int size) {
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
    if (fileSizeBytes_ != std::numeric_limits<int>::min() && ebookPtr->getFileSizeBytes() != fileSizeBytes_)
        return false;

    // DRM filter
    if (drm_ && ebookPtr->hasDrm() != drm_)
        return false;

    return true;
}

void Ebook::accept(IConstMediaVisitor &v) const {
    // Dynamic cast per MediaJSONVisitor
    if (auto* jsonVisitor = dynamic_cast<memory::MediaJSONVisitor*>(&v)) {
        jsonVisitor->visit(*this);
        return;
    }
    // Dynamic cast per MediaXMLVisitor
    if (auto* xmlVisitor = dynamic_cast<memory::MediaXMLVisitor*>(&v)) {
        xmlVisitor->visit(*this);
        return;
    }
    // Fallback: chiama il visit generico
    return;
}

}
