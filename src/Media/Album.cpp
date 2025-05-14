#include "Album.h"

namespace media {
Album::Album(const std::string &title, int release, const std::string &language,
             bool favourite, const std::vector<std::string> &genres,
             const std::string &img_path, const std::string &notes,
             const std::string &band,
             const std::vector<std::string> &band_members,
             const std::vector<std::string> &songs)
    : Media(title, release, language, favourite, genres, img_path, notes),
      band_(band),
      band_members_(band_members),
      songs_(songs) {}
const std::string &Album::getBand() const { return band_; }
const std::vector<std::string> &Album::getBandMembers() const {
  return band_members_;
}
const std::vector<std::string> &Album::getSongs() const { return songs_; }
}  // namespace media
