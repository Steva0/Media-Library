#ifndef MEDIA_SERIES_H
#define MEDIA_SERIES_H
#include "Movie.h"

namespace media {
class Series : public Movie {
 private:
  int episodes_;
  int seasons_;
  bool ended_;

 public:
  Series(const std::string &title, int release = std::numeric_limits<int>::min(), const std::string &language = "",
         bool favourite = false, const std::vector<std::string> &genres = {},
         const std::string &img_path = "", const std::string &notes = "",
         const std::vector<std::string> &cast = {}, int length = std::numeric_limits<int>::min(),
         const std::string &universe = "", int episodes = std::numeric_limits<int>::min(),
         int seasons = std::numeric_limits<int>::min(), bool ended = false);
  bool operator==(const Media &other) const override;
  int getEpisodes() const;
  int getSeasons() const;
  bool hasEnded() const;
  
  std::unique_ptr<Media> clone() const override;

  bool filter(const Media& input) const override;

  void accept(IConstMediaVisitor &) const override;
};
}  
#endif  // MEDIA_SERIES_H
