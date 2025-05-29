#ifndef MEDIA_MOVIE_H
#define MEDIA_MOVIE_H

#include <string>
#include <vector>

#include "Media.h"

namespace media {
class Movie : public Media {
 private:
  std::vector<std::string> cast_;
  int length_;
  std::string universe_;

 public:
  Movie(const std::string &title, int release = std::numeric_limits<int>::min(), const std::string &language = "",
        bool favourite = false, const std::vector<std::string> &genres = {},
        const std::string &img_path = "", const std::string &notes = "",
        const std::vector<std::string> &cast = {}, int length = std::numeric_limits<int>::min(),
        const std::string &universe = "");
  bool operator==(const Media &other) const override;
  const std::vector<std::string> &getCast() const;
  int getLength() const;
  const std::string &getUniverse() const;

  std::unique_ptr<Media> clone() const override;

  bool filter(const Media& movie) const override;

  void accept(IConstMediaVisitor &) const override;
};
}  // namespace media
#endif

