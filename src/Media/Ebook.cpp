#include "Ebook.h"

namespace media {

Ebook::Ebook(const std::string& title, int publicationYear, const std::string& language, bool favorite,
             const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
             const std::string& author, const std::string& publisher, int pages, const std::string& series,
             const std::string& isbn, int fileSizeBytes, bool drm)
    : Novel(title, publicationYear, language, favorite, genres, imagePath, notes, author, publisher, pages, series,
            isbn),
      fileSizeBytes_(fileSizeBytes > 0 ? fileSizeBytes : std::numeric_limits<int>::min()),
      drm_(drm) {}
Ebook::Ebook(const Novel& novel, int fileSizeBytes, bool drm)
    : Novel(novel), fileSizeBytes_(fileSizeBytes), drm_(drm) {}

bool Ebook::operator==(const Media& other) const {
  const auto* other_ebook = dynamic_cast<const Ebook*>(&other);
  if (other_ebook) {
    return Novel::operator==(*other_ebook) && fileSizeBytes_ == other_ebook->fileSizeBytes_ &&
           drm_ == other_ebook->drm_;
  }
  return false;
}

int Ebook::getFileSizeBytes() const { return fileSizeBytes_; }

bool Ebook::hasDrm() const { return drm_; }

void Ebook::setFileSizeBytes(int size) {
  fileSizeBytes_ = size;
  if (fileSizeBytes_ <= 0) fileSizeBytes_ = std::numeric_limits<int>::min();
}

void Ebook::setDrm(bool drm) { drm_ = drm; }

std::unique_ptr<Media> Ebook::makePtr() const { return std::make_unique<Ebook>(*this); }
std::string Ebook::displayType() const { return "EBOOK"; }

bool Ebook::filter(const Media& input) const {
  // Riutilizzo filtro base di Novel
  if (!Novel::filter(input)) return false;
  // Cast to Ebook to access Ebook-specific members
  const Ebook* ebookPtr = dynamic_cast<const Ebook*>(&input);
  if (!ebookPtr) return false;

  // File size filter
  if (fileSizeBytes_ != std::numeric_limits<int>::min() && ebookPtr->getFileSizeBytes() != fileSizeBytes_) return false;

  // DRM filter
  if (drm_ && ebookPtr->hasDrm() != drm_) return false;

  return true;
}
void Ebook::accept(IConstMediaVisitor& v) const { v.visit(*this); }

}  // namespace media
