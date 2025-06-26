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
  explicit Album(const std::string &title, int release = std::numeric_limits<int>::min(),
                 const std::string &language = "", bool favourite = false, const std::vector<std::string> &genres = {},
                 const std::string &img_path = "", const std::string &notes = "", const std::string &band = "",
                 const std::vector<std::string> &band_members = {}, const std::vector<std::string> &songs = {});
  bool operator==(const Media &) const override;

  const std::string &getBand() const;
  const std::vector<std::string> &getBandMembers() const;
  const std::vector<std::string> &getSongs() const;

  void setBand(const std::string &name);
  void addMember(const std::string &member);
  void removeMember(const std::string &member);
  void addSong(const std::string &song);
  void removeSong(const std::string &song);

  std::unique_ptr<Media> makePtr() const override;

  bool filter(const Media &album) const override;
  void accept(IConstMediaVisitor &) const override;
};
}  // namespace media

#endif
