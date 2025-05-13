#ifndef MEDIA_SERIES_H
#define MEDIA_SERIES_H
#include "Movie.h"

namespace media {
class Series : public Movie {
 private:
  unsigned int episodes_;
  unsigned int seasons_;
  bool ended_;

 public:
  Series(const std::string &title, int release, const std::string &language,
         bool favourite, const std::vector<std::string> &genres,
         const std::string &img_path, const std::string &notes,
         const std::vector<std::string> &cast, unsigned int length,
         const std::string &universe, unsigned int episodes,
         unsigned int seasons, bool ended);
};
}  // namespace library::media
#endif
