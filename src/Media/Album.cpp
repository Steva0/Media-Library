#include "Album.h"

namespace media {
Album::Album(const std::string &title, int release, const std::string &language, bool favourite,
             const std::vector<std::string> &genres, const std::string &img_path, const std::string &notes,
             const std::string &band, const std::vector<std::string> &band_members,
             const std::vector<std::string> &songs)
    : Media(title, release, language, favourite, genres, img_path, notes),
      band_(band),
      band_members_(band_members),
      songs_(songs) {}
Album::Album(const Media &media, const std::string &band, const std::vector<std::string> &band_members,
             const std::vector<std::string> &songs)
    : Media(media), band_(band), band_members_(band_members), songs_(songs) {}

bool Album::operator==(const Media &other) const {
  const auto *other_album = dynamic_cast<const Album *>(&other);
  if (other_album) {
    return Media::operator==(*other_album) && band_ == other_album->band_ &&
           band_members_ == other_album->band_members_ && songs_ == other_album->songs_;
  }
  return false;
}

const std::string &Album::getBand() const { return band_; }
const std::vector<std::string> &Album::getBandMembers() const { return band_members_; }
const std::vector<std::string> &Album::getSongs() const { return songs_; }

void Album::setBand(const std::string &name) { band_ = name; }
void Album::addMember(const std::string &member) {
  if (member == "") return;
  if (std::find(band_members_.begin(), band_members_.end(), member) == band_members_.end())
    band_members_.push_back(member);
}
void Album::removeMember(const std::string &member) {
  auto it = std::find(band_members_.begin(), band_members_.end(), member);
  if (it != band_members_.end()) band_members_.erase(it);
}
void Album::addSong(const std::string &song) {
  if (song == "") return;
  if (std::find(songs_.begin(), songs_.end(), song) == songs_.end()) songs_.push_back(song);
}
void Album::removeSong(const std::string &song) {
  auto it = std::find(songs_.begin(), songs_.end(), song);
  if (it != songs_.end()) songs_.erase(it);
}

std::unique_ptr<Media> Album::makePtr() const { return std::make_unique<Album>(*this); }
std::string Album::displayType() const { return "ALBUM"; }

bool Album::filter(const Media &album) const {
  if (!Media::filter(album)) return false;

  const Album *albumPtr = dynamic_cast<const Album *>(&album);
  if (!albumPtr) return false;

  if (!band_.empty() && !stringContainsIgnoreCase(albumPtr->getBand(), band_)) return false;

  if (!band_members_.empty()) {
    // corrispondenza parziale case insensitive su tutti i membri
    for (const auto &memberFilter : band_members_) {
      bool found = false;
      for (const auto &m : albumPtr->getBandMembers()) {
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

  if (!songs_.empty()) {
    // corrispondenza parziale case insensitive su tutte le canzoni
    for (const auto &songFilter : songs_) {
      bool found = false;
      for (const auto &s : albumPtr->getSongs()) {
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

void Album::accept(IConstMediaVisitor &v) const { v.visit(*this); }

}  // namespace media
