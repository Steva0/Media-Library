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
         const std::string &universe, unsigned int episodes = std::numeric_limits<unsigned int>::max(),
         unsigned int seasons = std::numeric_limits<unsigned int>::max(), bool ended = false);
  bool operator==(const Media &other) const override;
  unsigned int getEpisodes() const;
  unsigned int getSeasons() const;
  bool isEnded() const;
};
}  // namespace media
#endif
