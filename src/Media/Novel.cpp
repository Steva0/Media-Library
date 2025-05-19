#include "Novel.h"
namespace media {

// Main constructor
Novel::Novel(const std::string& title, int publicationYear, const std::string& language,
             bool favorite, const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
             const std::string& author, const std::string& publisher,
             unsigned int pages, const std::string& series, const std::string& isbn)
    : Media(title, publicationYear, language, favorite, genres, imagePath, notes),
      author_(author), publisher_(publisher), pages_(pages), series_(series), isbn_(isbn) {}

bool Novel::operator==(const Media& other) const {
    const Novel* otherNovel = dynamic_cast<const Novel*>(&other);
    if (otherNovel) {
        return Media::operator==(*otherNovel) && author_ == otherNovel->author_ &&
               publisher_ == otherNovel->publisher_ && pages_ == otherNovel->pages_ &&
               series_ == otherNovel->series_ && isbn_ == otherNovel->isbn_;
    }
    return false;
}

// Getters
std::string Novel::getAuthor() const { return author_; }
std::string Novel::getPublisher() const { return publisher_; }
unsigned int Novel::getPages() const { return pages_; }
std::string Novel::getSeries() const { return series_; }
std::string Novel::getIsbn() const { return isbn_; }

// Setters
void Novel::setAuthor(const std::string& author) { author_ = author; }
void Novel::setPublisher(const std::string& publisher) { publisher_ = publisher; }
void Novel::setPages(unsigned int pages) { pages_ = pages; }
void Novel::setSeries(const std::string& series) { series_ = series; }
void Novel::setIsbn(const std::string& isbn) { isbn_ = isbn; }

}