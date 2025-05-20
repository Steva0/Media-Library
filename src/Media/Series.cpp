#include "Series.h"

namespace media {
Series::Series(const std::string &title, int release,
               const std::string &language, bool favourite,
               const std::vector<std::string> &genres,
               const std::string &img_path, const std::string &notes,
               const std::vector<std::string> &cast, unsigned int length,
               const std::string &universe, unsigned int episodes,
               unsigned int seasons, bool ended)
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
unsigned int Series::getEpisodes() const { return episodes_; }
unsigned int Series::getSeasons() const { return seasons_; }
bool Series::isEnded() const { return ended_; }

std::vector<std::shared_ptr<Media>> Series::filter(const std::vector<std::shared_ptr<Series>>& input) const {
    std::vector<std::shared_ptr<Media>> result;

    // Riutilizzo filtro base di Movie (che a sua volta chiama Media::filter)
    std::vector<std::shared_ptr<Movie>> baseInput(input.begin(), input.end());
    std::vector<std::shared_ptr<Media>> filteredBase = Movie::filter(baseInput);

    for (const auto& mediaPtr : filteredBase) {
        auto seriesPtr = std::dynamic_pointer_cast<Series>(mediaPtr);
        if (!seriesPtr) continue;

        bool match = true;

        // Episodes (confronto stretto)
        if (episodes_ != std::numeric_limits<unsigned int>::max() && seriesPtr->getEpisodes() != episodes_)
            match = false;

        // Seasons (confronto stretto)
        if (seasons_ != std::numeric_limits<unsigned int>::max() && seriesPtr->getSeasons() != seasons_)
            match = false;

        // Ended (confronto booleano)
        if (ended_ && ended_ != seriesPtr->isEnded())
            match = false;

        if (match)
            result.push_back(seriesPtr);
    }

    return result;
}

}  // namespace media
