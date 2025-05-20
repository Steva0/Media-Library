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

bool Movie::filter(const Media& movie) const {

    if (!Media::filter(movie))
        return false;

    // Cast (match parziale, case-insensitive)
    const Movie* moviePtr = dynamic_cast<const Movie*>(&movie);
    if (!moviePtr) {
        return false;
    }
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
                return false;
            }
        }
    }

    // Length (confronto stretto)
    if (length_ != std::numeric_limits<unsigned int>::max() && moviePtr->getLength() != length_)
        return false;

    // Universe (match parziale, case-insensitive)
    if (!universe_.empty() && !stringContainsIgnoreCase(moviePtr->getUniverse(), universe_))
        return false;
    
    return true;
}


}  // namespace media


