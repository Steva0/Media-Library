#ifndef MEMORY_MEDIA_CONTAINER_H
#define MEMORY_MEDIA_CONTAINER_H
#include "../Media/Media.h"

namespace memory {
class MediaContainer {
 public:
  MediaContainer() = default;
  int addMedia(media::Media *);
  int removeMedia(media::Media *);
  std::vector<media::Media *> filter(const media::Media *);
};
}  // namespace memory
#endif
