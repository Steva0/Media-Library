#include "Novel.h"
namespace media {

// Main constructor
Novel::Novel(const std::string& title, int publicationYear, const std::string& language, bool favorite,
             const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
             const std::string& author, const std::string& publisher, int pages, const std::string& series,
             const std::string& isbn)
    : Media(title, publicationYear, language, favorite, genres, imagePath, notes),
      author_(author),
      publisher_(publisher),
      pages_(pages > 0 ? pages : std::numeric_limits<int>::min()),
      series_(series),
      isbn_(isbn) {}

Novel::Novel(const Media& media, const std::string& author, const std::string& publisher, int pages,
             const std::string& series, const std::string& isbn)
    : Media(media), author_(author), publisher_(publisher), pages_(pages), series_(series), isbn_(isbn) {}

bool Novel::operator==(const Media& other) const {
  const auto* other_novel = dynamic_cast<const Novel*>(&other);
  if (other_novel) {
    return Media::operator==(*other_novel) && author_ == other_novel->author_ &&
           publisher_ == other_novel->publisher_ && pages_ == other_novel->pages_ && series_ == other_novel->series_ &&
           isbn_ == other_novel->isbn_;
  }
  return false;
}

std::unique_ptr<Media> Novel::makePtr() const { return std::make_unique<Novel>(*this); }
std::string Novel::displayType() const { return "LIBRO"; }

// Getters
const std::string& Novel::getAuthor() const { return author_; }
const std::string& Novel::getPublisher() const { return publisher_; }
int Novel::getPages() const { return pages_; }
const std::string& Novel::getSeries() const { return series_; }
const std::string& Novel::getIsbn() const { return isbn_; }

// Setters
void Novel::setAuthor(const std::string& author) { author_ = author; }
void Novel::setPublisher(const std::string& publisher) { publisher_ = publisher; }
void Novel::setPages(int pages) {
  pages_ = pages;
  if (pages <= 0) pages_ = std::numeric_limits<int>::min();
}
void Novel::setSeries(const std::string& series) { series_ = series; }
void Novel::setIsbn(const std::string& isbn) { isbn_ = isbn; }

bool Novel::filter(const Media& input) const {
  // Riutilizzo filtro base di Media
  if (!Media::filter(input)) return false;
  // Cast to Novel to access Novel-specific members
  const Novel* novelPtr = dynamic_cast<const Novel*>(&input);
  if (!novelPtr) return false;

  // Match fields
  // Autore
  if (!author_.empty() && !stringContainsIgnoreCase(novelPtr->getAuthor(), author_)) return false;

  // Editore
  if (!publisher_.empty() && !stringContainsIgnoreCase(novelPtr->getPublisher(), publisher_)) return false;

  // Serie
  if (!series_.empty() && !stringContainsIgnoreCase(novelPtr->getSeries(), series_)) return false;

  // ISBN
  if (!isbn_.empty() && !stringContainsIgnoreCase(novelPtr->getIsbn(), isbn_)) return false;

  // Pagine (non fa il confronto)

  return true;
}

void Novel::accept(IConstMediaVisitor& v) const { v.visit(*this); }

}  // namespace media
