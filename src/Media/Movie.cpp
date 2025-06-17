#include "Movie.h"

namespace media {
Movie::Movie(const std::string &title, int release, const std::string &language,
             bool favourite, const std::vector<std::string> &genres,
             const std::string &img_path, const std::string &notes,
             const std::vector<std::string> &cast, int length,
             const std::string &universe)
    : Media(title, release, language, favourite, genres, img_path, notes),
      cast_(cast),
      length_(length> 0 ? length : std::numeric_limits<int>::min()), // Default to min if length is invalid
      universe_(universe) {}
bool Movie::operator==(const Media &other) const {
    const Movie *otherMovie = dynamic_cast<const Movie *>(&other);
    if (otherMovie) {
        return Media::operator==(*otherMovie) && cast_ == otherMovie->cast_ &&
               length_ == otherMovie->length_ && universe_ == otherMovie->universe_;
    }
    return false;
}

std::unique_ptr<Media> Movie::makePtr() const {
    return std::make_unique<Movie>(*this);
}

const std::vector<std::string> &Movie::getCast() const { return cast_; }
int Movie::getLength() const { return length_; }
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

    // Length (non confronto)

    // Universe (match parziale, case-insensitive)
    if (!universe_.empty() && !stringContainsIgnoreCase(moviePtr->getUniverse(), universe_))
        return false;
    
    return true;
}

void Movie::accept(IConstMediaVisitor &v) const {
    // Dynamic cast per MediaJSONVisitor
    if (auto* jsonVisitor = dynamic_cast<memory::MediaJSONVisitor*>(&v)) {
        jsonVisitor->visit(*this);
        return;
    }
    // Dynamic cast per MediaXMLVisitor
    if (auto* xmlVisitor = dynamic_cast<memory::MediaXMLVisitor*>(&v)) {
        xmlVisitor->visit(*this);
        return;
    }
    // Fallback: chiama il visit generico
    return;
}


}  // namespace media


