#ifndef MEDIA_MEDIA_H
#define MEDIA_MEDIA_H
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "StringUtils.h"
#include "IConstMediaVisitor.h"

namespace media {
class Media {
 private:
  std::string title_;
  int release_;
  std::string language_;
  bool favourite_;
  std::vector<std::string> genres_;
  std::string img_path_;
  std::string notes_;

 public:
  explicit Media(const std::string &title = "", int release = std::numeric_limits<int>::min(),
                 const std::string &language = "", bool favourite = false, const std::vector<std::string> &genres = {},
                 const std::string &img_path = "", const std::string &notes = "");
  virtual ~Media() = default;
  virtual bool operator==(const Media &) const;

  virtual void accept(IConstMediaVisitor &) const;

  const std::string &getTitle() const;
  int getRelease() const;
  const std::string &getLanguage() const;
  bool isFavourite() const;
  const std::vector<std::string> &getGenres() const;
  const std::string &getImgPath() const;
  const std::string &getNotes() const;

  void setTitle(const std::string &);
  void setRelease(int);
  void setLanguage(const std::string &);
  void setFavourite(bool);
  void addGenre(const std::string &);
  void clearGenres();
  void setImgPath(const std::string &);
  void setNotes(const std::string &);

  virtual std::unique_ptr<Media> makePtr() const;
  virtual std::string displayType() const;

  virtual bool filter(const Media &media) const;
};
}  // namespace media
#endif
