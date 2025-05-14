#include "Romanzo.h"
namespace media {

// Main constructor
Romanzo::Romanzo(const std::string& title, int publicationYear, const std::string& language,
             bool favorite, const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
             const std::string& author, const std::string& publisher,
             unsigned int pages, const std::string& series, const std::string& isbn)
    : Media(title, publicationYear, language, favorite, genres, imagePath, notes),
      author_(author), publisher_(publisher), pages_(pages), series_(series), isbn_(isbn) {}

// Copy constructor
Romanzo::Romanzo(const Romanzo& other)
    : Media(other),
      author_(other.author_), publisher_(other.publisher_),
      pages_(other.pages_), series_(other.series_), isbn_(other.isbn_) {}

// Copy assignment operator
Romanzo& Romanzo::operator=(const Romanzo& other) {
    if (this != &other) {
        Media::operator=(other);
        author_ = other.author_;
        publisher_ = other.publisher_;
        pages_ = other.pages_;
        series_ = other.series_;
        isbn_ = other.isbn_;
    }
    return *this;
}

// Visitor
void Romanzo::accept(IMediaVisitor& v) const {
    v.visit(*this);
}

// Getters
std::string Romanzo::getAuthor() const { return author_; }
std::string Romanzo::getPublisher() const { return publisher_; }
unsigned int Romanzo::getPages() const { return pages_; }
std::string Romanzo::getSeries() const { return series_; }
std::string Romanzo::getIsbn() const { return isbn_; }

// Setters
void Romanzo::setAuthor(const std::string& author) { author_ = author; }
void Romanzo::setPublisher(const std::string& publisher) { publisher_ = publisher; }
void Romanzo::setPages(unsigned int pages) { pages_ = pages; }
void Romanzo::setSeries(const std::string& series) { series_ = series; }
void Romanzo::setIsbn(const std::string& isbn) { isbn_ = isbn; }

}