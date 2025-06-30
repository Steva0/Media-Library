#ifndef MEDIA_EBOOK_H
#define MEDIA_EBOOK_H

#include "Novel.h"

namespace media {

class Ebook : public Novel {
 private:
  int fileSizeBytes_;
  bool drm_;

 public:
  explicit Ebook(const std::string& title = "", int publicationYear = std::numeric_limits<int>::min(),
                 const std::string& language = "", bool favorite = false, const std::vector<std::string>& genres = {},
                 const std::string& imagePath = "", const std::string& notes = "", const std::string& author = "",
                 const std::string& publisher = "", int pages = std::numeric_limits<int>::min(),
                 const std::string& series = "", const std::string& isbn = "",
                 int fileSizeBytes = std::numeric_limits<int>::min(), bool drm = false);
  explicit Ebook(const Novel&, int fileSizeBytes = std::numeric_limits<int>::min(), bool drm = false);
  bool operator==(const Media&) const override;

  int getFileSizeBytes() const;
  bool hasDrm() const;

  void setFileSizeBytes(int size);
  void setDrm(bool drm);

  std::unique_ptr<Media> makePtr() const override;

  bool filter(const Media& input) const override;

  void accept(IConstMediaVisitor&) const override;
};

}  // namespace media

#endif  // MEDIA_EBOOK_H
