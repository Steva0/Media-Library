#include "Movie.h"

namespace media {
Movie::Movie(const std::string &title, int release, const std::string &language,
             bool favourite, const std::vector<std::string> &genres,
             const std::string &img_path, const std::string &notes,
             const std::vector<std::string> &cast, unsigned int length,
             const std::string &universe)
    : Media(title, release, language, favourite, genres, img_path, notes),
      cast_(cast),
      length_(length),
      universe_(universe) {}
bool Movie::operator==(const Media &other) const {
    const Movie *otherMovie = dynamic_cast<const Movie *>(&other);
    if (otherMovie) {
        return Media::operator==(*otherMovie) && cast_ == otherMovie->cast_ &&
               length_ == otherMovie->length_ && universe_ == otherMovie->universe_;
    }
    return false;
}
const std::vector<std::string> &Movie::getCast() const { return cast_; }
unsigned int Movie::getLength() const { return length_; }
const std::string &Movie::getUniverse() const { return universe_; }

std::vector<std::shared_ptr<Media>> Movie::filter(const std::vector<std::shared_ptr<Movie>>& input) const {
    std::vector<std::shared_ptr<Media>> result;

    // Riutilizza filtro base di Media (poiché Movie deriva da Media)
    std::vector<std::shared_ptr<Media>> baseInput(input.begin(), input.end());
    std::vector<std::shared_ptr<Media>> filteredBase = Media::filter(baseInput);

    for (const auto& mediaPtr : filteredBase) {
        auto moviePtr = std::dynamic_pointer_cast<Movie>(mediaPtr);
        if (!moviePtr) continue;

        bool match = true;

        // Cast (match parziale, case-insensitive)
        if (!cast_.empty()) {
            const auto& movieCast = moviePtr->getCast();
            for (const auto& filterCast : cast_) {
                bool found = false;
                for (const auto& member : movieCast) {
                    if (stringContainsIgnoreCase(member, filterCast)) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    match = false;
                    break;
                }
            }
        }

        // Length (confronto stretto)
        if (length_ != std::numeric_limits<unsigned int>::max() && moviePtr->getLength() != length_)
            match = false;

        // Universe (match parziale, case-insensitive)
        if (!universe_.empty() && !stringContainsIgnoreCase(moviePtr->getUniverse(), universe_))
            match = false;

        if (match)
            result.push_back(moviePtr);
    }

    return result;
}


}  // namespace media
