#ifndef EBOOK_H
#define EBOOK_H

#include "Novel.h"

namespace media {

class Ebook : public Novel {
private:
    unsigned int fileSizeBytes_;
    bool drm_;

public:
    Ebook(const std::string& title, int publicationYear, const std::string& language,
          bool favorite, const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
          const std::string& author, const std::string& publisher,
          unsigned int pages, const std::string& series, const std::string& isbn,
          unsigned int fileSizeBytes, bool drm);

    void accept(IConstMediaVisitor& v) const override;

    unsigned int getFileSizeBytes() const;
    bool hasDrm() const;

    void setFileSizeBytes(unsigned int size);
    void setDrm(bool drm);
};

}

#endif // EBOOK_H