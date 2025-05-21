#ifndef MEMORY_MEDIACONTAINER_H
#define MEMORY_MEDIACONTAINER_H

#include <QSaveFile>
#include <array>
#include <memory>
#include <vector>

#include "../Media/Album.h"
#include "../Media/AudioBook.h"
#include "../Media/Ebook.h"
#include "../Media/Movie.h"
#include "../Media/Novel.h"
#include "../Media/Series.h"

namespace memory {

class MediaContainer {
 private:

 public:
  void addMedia(const media::Media& media);
  void addMedia(const std::vector<media::Media>&);  // placeholder
  void removeMedia(const media::Media& media);
  void clear();

  // Filtri
  std::vector<std::shared_ptr<media::Media>> filter(
      const media::Media& media) const;

  int serialize(QSaveFile& file) const;
};

}  // namespace memory

#endif  // MEMORY_MEDIACONTAINER_H
