#ifndef MEDIA_MEDIA_H
#define MEDIA_MEDIA_H
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "IMedia.h"
#include "StringUtils.h"

namespace media {
class Media : IMedia {
 private:
  std::string title_;
  int release_;
  std::string language_;
  bool favourite_;
  std::vector<std::string> genres_;
  std::string img_path_;
  std::string notes_;
  static int debug_count_;

 public:
  explicit Media(const std::string &title = "", int release = std::numeric_limits<int>::min(),
                 const std::string &language = "", bool favourite = false, const std::vector<std::string> &genres = {},
                 const std::string &img_path = "", const std::string &notes = "");
  Media(const Media &o) {
    title_ = o.title_;
    release_ = o.release_;
    language_ = o.language_;
    favourite_ = o.favourite_;
    genres_ = o.genres_;
    img_path_ = o.img_path_;
    notes_ = o.notes_;

    debug_count_++;
    std::cout << "(" << debug_count_ << ") Media(const Media&): " << title_ << std::endl;
  }
  ~Media() override {
    debug_count_--;
    std::cout << "(" << debug_count_ << ") ~Media(): " << title_ << std::endl;
  }
  virtual bool operator==(const Media &) const;

  void accept(IConstMediaVisitor &) const override;
  bool open() override;

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

  std::unique_ptr<Media> makePtr() const override;
  std::string displayType() const override;

  virtual bool filter(const Media &media) const;
};
}  // namespace media
#endif
