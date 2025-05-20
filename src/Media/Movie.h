#ifndef MEDIA_MOVIE_H
#define MEDIA_MOVIE_H

#include <string>
#include <vector>

#include "Media.h"

namespace media {
class Movie : public Media {
 private:
  std::vector<std::string> cast_;
  unsigned int length_;
  std::string universe_;

 public:
  Movie(const std::string &title, int release, const std::string &language,
        bool favourite, const std::vector<std::string> &genres,
        const std::string &img_path, const std::string &notes,
        const std::vector<std::string> &cast = {}, unsigned int length = std::numeric_limits<unsigned int>::max(),
        const std::string &universe = "");
  bool operator==(const Media &other) const override;
  const std::vector<std::string> &getCast() const;
  unsigned int getLength() const;
  const std::string &getUniverse() const;
};
}  // namespace media
#endif
