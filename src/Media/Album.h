#ifndef MEDIA_ALBUM_H
#define MEDIA_ALBUM_H

#include "Media.h"
namespace media {
class Album : public Media {
 private:
  std::string band_;
  std::vector<std::string> band_members_;
  std::vector<std::string> songs_;

 public:
  Album(const std::string &title, int release, const std::string &language,
        bool favourite, const std::vector<std::string> &genres,
        const std::string &img_path, const std::string &notes,
        const std::string &band, const std::vector<std::string> &band_members,
        const std::vector<std::string> &songs);
};
}  // namespace library::media
#endif
