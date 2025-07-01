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
  explicit Series(const std::string &title = "", int release = std::numeric_limits<int>::min(),
                  const std::string &language = "", bool favourite = false, const std::vector<std::string> &genres = {},
                  const std::string &img_path = "", const std::string &notes = "",
                  const std::vector<std::string> &cast = {}, int length = std::numeric_limits<int>::min(),
                  const std::string &universe = "", int episodes = std::numeric_limits<int>::min(),
                  int seasons = std::numeric_limits<int>::min(), bool ended = false);
  explicit Series(const Movie &movie, int episodes = std::numeric_limits<int>::min(),
                  int seasons = std::numeric_limits<int>::min(), bool ended = false);

  bool operator==(const Media &) const override;
  int getEpisodes() const;
  int getSeasons() const;
  bool hasEnded() const;

  void setEpisodes(int);
  void setSeasons(int);
  void setEnded(bool);

  std::unique_ptr<Media> makePtr() const override;
  std::string displayType() const override;

  bool filter(const Media &input) const override;

  void accept(IConstMediaVisitor &) const override;
};
}  // namespace media
#endif  // MEDIA_SERIES_H
