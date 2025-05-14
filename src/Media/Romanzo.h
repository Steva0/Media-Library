#ifndef Romanzo_H
#define Romanzo_H

#include "Media.h"

namespace media {

class Romanzo : public Media {
private:
    std::string author_;
    std::string publisher_;
    unsigned int pages_;
    std::string series_;
    std::string isbn_;

public:
    Romanzo(const std::string& title, int publicationYear, const std::string& language,
          bool favorite, const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
          const std::string& author, const std::string& publisher,
          unsigned int pages, const std::string& series, const std::string& isbn);

    // Copy constructor and assignment operator
    Romanzo(const Romanzo& other);
    Romanzo& operator=(const Romanzo& other);

    // Virtual methods
    void accept(IConstMediaVisitor& v) const override;

    // Getters
    std::string getAuthor() const;
    std::string getPublisher() const;
    unsigned int getPages() const;
    std::string getSeries() const;
    std::string getIsbn() const;

    // Setters
    void setAuthor(const std::string& author);
    void setPublisher(const std::string& publisher);
    void setPages(unsigned int pages);
    void setSeries(const std::string& series);
    void setIsbn(const std::string& isbn);
};
}
#endif // Romanzo_H