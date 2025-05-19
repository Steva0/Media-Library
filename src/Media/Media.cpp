#include "Media.h"

namespace media {
Media::Media(const std::string &title, int release, const std::string &language,
             bool favourite, const std::vector<std::string> &genres,
             const std::string &img_path, const std::string &notes)
    : title_(title),
      release_(release),
      language_(language),
      favourite_(favourite),
      genres_(genres),
      img_path_(img_path),
      notes_(notes) {}

void Media::accept(IConstMediaVisitor &v) const {}

bool Media::operator==(const Media &other) const {
  return title_ == other.title_ && release_ == other.release_ &&
         language_ == other.language_ && favourite_ == other.favourite_ &&
         genres_ == other.genres_ && img_path_ == other.img_path_ &&
         notes_ == other.notes_;
}

bool Media::open() {
  notes_ = "";
  std::cout<< "Media::open()" << std::endl;  
  return false;
}

const std::string &Media::getTitle() const { return title_; }
int Media::getRelease() const { return release_; }
const std::string &Media::getLanguage() const { return language_; };
bool Media::isFavourite() const { return favourite_; }
const std::vector<std::string> &Media::getGenres() const { return genres_; }
const std::string &Media::getImgPath() const { return img_path_; }
const std::string &Media::getNotes() const { return notes_; }

}  // namespace media
