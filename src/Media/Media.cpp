#include "Media.h"
#include <limits>
#include <cctype>
#include <locale>
#include <algorithm>

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

void Media::accept(IConstMediaVisitor &v) const {
    v.visit(*this);
}

std::unique_ptr<media::Media> media::Media::makePtr() const {
    return std::make_unique<media::Media>(*this);
}


bool Media::operator==(const Media &other) const {
  return title_ == other.title_ && release_ == other.release_ &&
         language_ == other.language_ && favourite_ == other.favourite_ &&
         genres_ == other.genres_ && img_path_ == other.img_path_ &&
         notes_ == other.notes_;
}

bool Media::open() {
  notes_ = "";
  return false;
}

void Media::setTitle(const std::string &title) {
    title_ = title;
}

bool Media::filter(const Media& media) const {
        // Title (substring, case-insensitive)
    if (!getTitle().empty() && !stringContainsIgnoreCase(media.getTitle(), getTitle()))
        return false;

    // Release (confronto stretto)
    if (getRelease() != std::numeric_limits<int>::min() &&
        media.getRelease() != getRelease())
        return false;

    // Language (substring, case-insensitive)
    if (!getLanguage().empty() && media.getLanguage() != getLanguage())
        return false;

    // Favourite (confronto booleano)
    if (isFavourite() && media.isFavourite() != isFavourite())
        return false;

    // Generi (match parziale case-insensitive su ogni genere richiesto)
    if (!getGenres().empty()) {
        const auto& mediaGenres = media.getGenres();
        for (const auto& genreFilter : getGenres()) {
            bool found = false;
            for (const auto& g : mediaGenres) {
                if (stringContainsIgnoreCase(g, genreFilter)) {
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


const std::string &Media::getTitle() const { return title_; }
int Media::getRelease() const { return release_; }
const std::string &Media::getLanguage() const { return language_; };
bool Media::isFavourite() const { return favourite_; }
const std::vector<std::string> &Media::getGenres() const { return genres_; }
const std::string &Media::getImgPath() const { return img_path_; }
const std::string &Media::getNotes() const { return notes_; }

}  // namespace media
