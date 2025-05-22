#include "Series.h"
#include "Media/IConstMediaVisitor.h"

namespace media {
Series::Series(const std::string &title, int release,
               const std::string &language, bool favourite,
               const std::vector<std::string> &genres,
               const std::string &img_path, const std::string &notes,
               const std::vector<std::string> &cast, int length,
               const std::string &universe, int episodes,
               int seasons, bool ended)
    : Movie(title, release, language, favourite, genres, img_path, notes, cast,
            length, universe),
      episodes_(episodes),
      seasons_(seasons),
      ended_(ended) {}
bool Series::operator==(const Media &other) const {
    const Series *otherSeries = dynamic_cast<const Series *>(&other);
    if (otherSeries) {
        return Movie::operator==(*otherSeries) && episodes_ == otherSeries->episodes_ &&
               seasons_ == otherSeries->seasons_ && ended_ == otherSeries->ended_;
    }
    return false;
}

std::unique_ptr<Media> Series::clone() const {
    return std::make_unique<Series>(*this);
}

int Series::getEpisodes() const { return episodes_; }
int Series::getSeasons() const { return seasons_; }
bool Series::hasEnded() const { return ended_; }

bool Series::filter(const Media& input) const {
     if (!Movie::filter(input))
        return false;

    const Series* seriesPtr = dynamic_cast<const Series*>(&input);
    if (!seriesPtr)
        return false; // Protegge da cast fallito

    // Episodes (confronto stretto)
    if (episodes_ != -1 && seriesPtr->getEpisodes() != episodes_)
        return false;

    // Seasons (confronto stretto)
    if (seasons_ != -1 && seriesPtr->getSeasons() != seasons_)
        return false;

    // Ended (confronto booleano)
    if (ended_ && ended_ != seriesPtr->hasEnded())
        return false;

    return true;
}

void Series::accept(IConstMediaVisitor &v) const { v.visit(*this); }

}  // namespace media
