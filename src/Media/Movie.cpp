#include "Movie.h"

#include <limits>

namespace media {
Movie::Movie(const std::string &title, int release, const std::string &language, bool favourite,
             const std::vector<std::string> &genres, const std::string &img_path, const std::string &notes,
             const std::vector<std::string> &cast, int length, const std::string &universe)
    : Media(title, release, language, favourite, genres, img_path, notes),
      cast_(cast),
      length_(length > 0 ? length : std::numeric_limits<int>::min()),  // Default to min if length is invalid
      universe_(universe) {}

Movie::Movie(const Media &media, const std::vector<std::string> &cast, int length, const std::string &universe)
    : Media(media), cast_(cast), length_(length), universe_(universe) {}

bool Movie::operator==(const Media &other) const {
  const auto *other_movie = dynamic_cast<const Movie *>(&other);
  if (other_movie) {
    return Media::operator==(*other_movie) && cast_ == other_movie->cast_ && length_ == other_movie->length_ &&
           universe_ == other_movie->universe_;
  }
  return false;
}

std::unique_ptr<Media> Movie::makePtr() const { return std::make_unique<Movie>(*this); }
std::string Movie::displayType() const { return "FILM"; }

const std::vector<std::string> &Movie::getCast() const { return cast_; }
int Movie::getLength() const { return length_; }
const std::string &Movie::getUniverse() const { return universe_; }

void Movie::addActor(const std::string &name) {
  if (name == "") return;
  if (std::find(cast_.begin(), cast_.end(), name) == cast_.end()) cast_.push_back(name);
}
void Movie::removeActor(const std::string &name) {
  auto it = std::find(cast_.begin(), cast_.end(), name);
  if (it != cast_.end()) cast_.erase(it);
}
void Movie::setLength(int length) {
  length_ = length;
  if (length <= 0) length_ = std::numeric_limits<int>::min();
}
void Movie::setUniverse(const std::string &universe) { universe_ = universe; }

bool Movie::filter(const Media &movie) const {
  if (!Media::filter(movie)) return false;

  // Cast (match parziale, case-insensitive)
  const Movie *moviePtr = dynamic_cast<const Movie *>(&movie);
  if (!moviePtr) {
    return false;
  }
  if (!cast_.empty()) {
    const auto &movieCast = moviePtr->getCast();
    for (const auto &filterCast : cast_) {
      bool found = false;
      for (const auto &member : movieCast) {
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
  if (!universe_.empty() && !stringContainsIgnoreCase(moviePtr->getUniverse(), universe_)) return false;

  return true;
}

void Movie::accept(IConstMediaVisitor &v) const { v.visit(*this); }

}  // namespace media
