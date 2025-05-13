#ifndef MEDIA_MEDIA_H
#define MEDIA_MEDIA_H
#include <string>
#include <vector>
#include "IMediaVisitor.h"

namespace media {
class Media {
 private:
  std::string title_;
  int release_;
  std::string language_;
  bool favourite_;
  std::vector<std::string> genres_;
  std::string img_path_;
  std::string notes_;

 public:
  Media(const std::string &title, int release, const std::string &language,
        bool favourite, const std::vector<std::string> &genres,
        const std::string &img_path, const std::string &notes);
  virtual void accept(IMediaVisitor &) const = 0;
};
}  // namespace library::media
#endif
