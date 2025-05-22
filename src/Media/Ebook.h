#ifndef MEDIA_EBOOK_H
#define MEDIA_EBOOK_H

#include "Novel.h"

namespace media {

class Ebook : public Novel {
private:
    int fileSizeBytes_;
    bool drm_;

public:
    Ebook(const std::string& title, int publicationYear, const std::string& language,
          bool favorite, const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
          const std::string& author, const std::string& publisher,
          int pages, const std::string& series, const std::string& isbn,
          int fileSizeBytes = -1, bool drm = false);

    bool operator==(const Media& other) const override;

    int getFileSizeBytes() const;
    bool hasDrm() const;

    void setFileSizeBytes(int size);
    void setDrm(bool drm);

    std::unique_ptr<Media> clone() const override;

    bool filter(const Media& ebook) const override;

    void accept(IConstMediaVisitor &) const override;

};

}

#endif // MEDIA_EBOOK_H
