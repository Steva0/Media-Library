#include "Media.h"

namespace media {
Media::Media(const std::string &title, int release, const std::string &language,
             bool favourite, const std::vector<std::string> &genres,
             const std::string &img_path, const std::string &notes)
    : title_(title),
      release_(release),
      favourite_(favourite),
      genres_(genres),
      img_path_(img_path),
      notes_(notes) {}
}  // namespace library::media
