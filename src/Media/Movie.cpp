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
}  // namespace library::media
