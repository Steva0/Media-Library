#include "Series.h"

namespace media {
Series::Series(const std::string &title, int release, const std::string &language, bool favourite,
               const std::vector<std::string> &genres, const std::string &img_path, const std::string &notes,
               const std::vector<std::string> &cast, int length, const std::string &universe, int episodes, int seasons,
               bool ended)
    : Movie(title, release, language, favourite, genres, img_path, notes, cast, length, universe),
      episodes_(episodes > 0 ? episodes : std::numeric_limits<int>::min()),  // Default to min if episodes is invalid
      seasons_(seasons > 0 ? seasons : std::numeric_limits<int>::min()),     // Default to min if seasons is invalid
      ended_(ended) {}

Series::Series(const Movie &movie, int episodes, int seasons, bool ended)
    : Movie(movie), episodes_(episodes), seasons_(seasons), ended_(ended) {}

bool Series::operator==(const Media &other) const {
  const auto *other_series = dynamic_cast<const Series *>(&other);
  if (other_series) {
    return Movie::operator==(*other_series) && episodes_ == other_series->episodes_ &&
           seasons_ == other_series->seasons_ && ended_ == other_series->ended_;
  }
  return false;
}

std::unique_ptr<Media> Series::makePtr() const { return std::make_unique<Series>(*this); }
std::string Series::displayType() const {return "SERIE";}

int Series::getEpisodes() const { return episodes_; }
int Series::getSeasons() const { return seasons_; }
bool Series::hasEnded() const { return ended_; }

void Series::setEpisodes(int episodes) {
  episodes_ = episodes;
  if (episodes_ <= 0) episodes_ = std::numeric_limits<int>::min();
}
void Series::setSeasons(int seasons) {
  seasons_ = seasons;
  if (seasons_ <= 0) seasons_ = std::numeric_limits<int>::min();
}
void Series::setEnded(bool ended) { ended_ = ended; }

bool Series::filter(const Media &input) const {
  if (!Movie::filter(input)) return false;

  const Series *seriesPtr = dynamic_cast<const Series *>(&input);
  if (!seriesPtr) return false; 

  if (episodes_ != std::numeric_limits<int>::min() && seriesPtr->getEpisodes() != episodes_) return false;

  if (seasons_ != std::numeric_limits<int>::min() && seriesPtr->getSeasons() != seasons_) return false;

  if (ended_ && ended_ != seriesPtr->hasEnded()) return false;

  return true;
}

void Series::accept(IConstMediaVisitor &v) const { v.visit(*this); }

}  // namespace media
