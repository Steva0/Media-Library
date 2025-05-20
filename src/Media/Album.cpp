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
bool Album::operator==(const Media &other) const {
  const Album *other_album = dynamic_cast<const Album *>(&other);
  if (other_album) {
    return Media::operator==(*other_album) && band_ == other_album->band_ &&
           band_members_ == other_album->band_members_ &&
           songs_ == other_album->songs_;
  }
  return false;
}

std::vector<std::shared_ptr<Media>> Album::filter(const std::vector<std::shared_ptr<Album>>& input) const {
    std::vector<std::shared_ptr<Media>> result;

    // Riutilizzo filtro base di Media
    std::vector<std::shared_ptr<Media>> baseInput(input.begin(), input.end());
    std::vector<std::shared_ptr<Media>> filteredBase = Media::filter(baseInput);

    // Filtro specifico per Album
    for (const auto& mediaPtr : filteredBase) {
        auto albumPtr = std::dynamic_pointer_cast<Album>(mediaPtr);
        if (!albumPtr) continue;

        bool match = true;

        // Band
        if (!band_.empty() && !stringContainsIgnoreCase(albumPtr->getBand(), band_))
            match = false;

        // Band members (ogni membro richiesto deve matchare almeno uno esistente)
        if (!band_members_.empty()) {
            for (const auto& memberFilter : band_members_) {
                bool found = false;
                for (const auto& m : albumPtr->getBandMembers()) {
                    if (stringContainsIgnoreCase(m, memberFilter)) {
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

        // Songs (ogni canzone richiesta deve matchare almeno una esistente)
        if (!songs_.empty()) {
            for (const auto& songFilter : songs_) {
                bool found = false;
                for (const auto& s : albumPtr->getSongs()) {
                    if (stringContainsIgnoreCase(s, songFilter)) {
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

        if (match)
            result.push_back(albumPtr);
    }

    return result;
}


}  // namespace media
