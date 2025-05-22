#ifndef MEDIA_SERIES_H
#define MEDIA_SERIES_H
#include "Media/IConstMediaVisitor.h"
#include "Movie.h"

namespace media {
class Series : public Movie {
 private:
  int episodes_;
  int seasons_;
  bool ended_;

 public:
  Series(const std::string &title, int release, const std::string &language,
         bool favourite, const std::vector<std::string> &genres,
         const std::string &img_path, const std::string &notes,
         const std::vector<std::string> &cast, int length,
         const std::string &universe, int episodes = -1,
         int seasons = -1, bool ended = false);
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
