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

std::unique_ptr<Media> Album::makePtr() const {
    return std::make_unique<Album>(*this);
}


bool Album::filter(const Media& album) const {
    // Riutilizzo filtro base di Media
    if (!Media::filter(album))
        return false;

    // Cast to Album to access Album-specific members
    const Album* albumPtr = dynamic_cast<const Album*>(&album);
    if (!albumPtr)
        return false;

    // Band
    if (!band_.empty() && !stringContainsIgnoreCase(albumPtr->getBand(), band_))
        return false;

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
                return false;
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
                return false;
            }
        }
    }
    return true;
}

void Album::accept(IConstMediaVisitor &v) const {
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
    return;
}

}  // namespace media
