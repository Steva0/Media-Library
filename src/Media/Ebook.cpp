#include "Ebook.h"

namespace media {

Ebook::Ebook(const std::string& title, int publicationYear, const std::string& language,
             bool favorite, const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
             const std::string& author, const std::string& publisher,
             unsigned int pages, const std::string& series, const std::string& isbn,
             unsigned int fileSizeBytes, bool drm)
    : Romanzo(title, publicationYear, language, favorite, genres, imagePath, notes,
            author, publisher, pages, series, isbn),
      fileSizeBytes_(fileSizeBytes), drm_(drm) {}

Ebook::Ebook(const Ebook& other)
    : Romanzo(other), fileSizeBytes_(other.fileSizeBytes_), drm_(other.drm_) {}

Ebook& Ebook::operator=(const Ebook& other) {
    if (this != &other) {
        Romanzo::operator=(other);
        fileSizeBytes_ = other.fileSizeBytes_;
        drm_ = other.drm_;
    }
    return *this;
}

void Ebook::accept(IMediaVisitor& v) const {
    v.visit(*this);
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

}