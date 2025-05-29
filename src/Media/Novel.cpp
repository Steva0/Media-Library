#include "Novel.h"
namespace media {

// Main constructor
Novel::Novel(const std::string& title, int publicationYear, const std::string& language,
             bool favorite, const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
             const std::string& author, const std::string& publisher,
             int pages, const std::string& series, const std::string& isbn)
    : Media(title, publicationYear, language, favorite, genres, imagePath, notes),
      author_(author), publisher_(publisher), pages_(pages > 0 ? pages : std::numeric_limits<int>::min()), series_(series), isbn_(isbn) {}

bool Novel::operator==(const Media& other) const {
    const Novel* otherNovel = dynamic_cast<const Novel*>(&other);
    if (otherNovel) {
        return Media::operator==(*otherNovel) && author_ == otherNovel->author_ &&
               publisher_ == otherNovel->publisher_ && pages_ == otherNovel->pages_ &&
               series_ == otherNovel->series_ && isbn_ == otherNovel->isbn_;
    }
    return false;
}

std::unique_ptr<Media> Novel::clone() const {
    return std::make_unique<Novel>(*this);
}

// Getters
std::string Novel::getAuthor() const { return author_; }
std::string Novel::getPublisher() const { return publisher_; }
int Novel::getPages() const { return pages_; }
std::string Novel::getSeries() const { return series_; }
std::string Novel::getIsbn() const { return isbn_; }

// Setters
void Novel::setAuthor(const std::string& author) { author_ = author; }
void Novel::setPublisher(const std::string& publisher) { publisher_ = publisher; }
void Novel::setPages(int pages) { pages_ = pages; }
void Novel::setSeries(const std::string& series) { series_ = series; }
void Novel::setIsbn(const std::string& isbn) { isbn_ = isbn; }


bool Novel::filter(const Media& input) const {
    // Riutilizzo filtro base di Media
    if (!Media::filter(input))
        return false;
    // Cast to Novel to access Novel-specific members
    const Novel* novelPtr = dynamic_cast<const Novel*>(&input);
    if (!novelPtr)
        return false;

    // Match fields
    // Autore
    if (!author_.empty() && !stringContainsIgnoreCase(novelPtr->getAuthor(), author_))
        return false;

    // Editore
    if (!publisher_.empty() && !stringContainsIgnoreCase(novelPtr->getPublisher(), publisher_))
        return false;

    // Serie
    if (!series_.empty() && !stringContainsIgnoreCase(novelPtr->getSeries(), series_))
        return false;

    // ISBN
    if (!isbn_.empty() && !stringContainsIgnoreCase(novelPtr->getIsbn(), isbn_))
        return false;

    // Pagine (non fa il confronto)

    return true;
}

void Novel::accept(IConstMediaVisitor &v) const {
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
