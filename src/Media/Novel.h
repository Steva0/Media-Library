#ifndef MEDIA_ROMANZO_H
#define MEDIA_ROMANZO_H

#include "Media.h"

namespace media {

class Novel : public Media {
private:
    std::string author_;
    std::string publisher_;
    int pages_;
    std::string series_;
    std::string isbn_;

public:
    Novel(const std::string& title, int publicationYear, const std::string& language,
          bool favorite, const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
          const std::string& author = "", const std::string& publisher = "",
          int pages = -1, const std::string& series = "", const std::string& isbn = "");

    bool operator==(const Media& other) const override;

    // Getters
    std::string getAuthor() const;
    std::string getPublisher() const;
    int getPages() const;
    std::string getSeries() const;
    std::string getIsbn() const;

    // Setters
    void setAuthor(const std::string& author);
    void setPublisher(const std::string& publisher);
    void setPages(int pages);
    void setSeries(const std::string& series);
    void setIsbn(const std::string& isbn);

    std::unique_ptr<Media> clone() const override;

    bool filter(const Media &novel) const override;

    void accept(IConstMediaVisitor &) const override;
};

}
#endif // MEDIA_ROMANZO_H
