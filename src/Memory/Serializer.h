#ifndef MEMORY_SERIALIZER_H
#define MEMORY_SERIALIZER_H
#include <QSaveFile>
#include "../Media/Media.h"

namespace memory {
class Serializer {
 private:
  static int vecToJSON(const std::vector<std::shared_ptr<media::Media>> &, QSaveFile &);
  static int vecToXML(const std::vector<std::shared_ptr<media::Media>> &, QSaveFile &);

 public:
  static int Serialize(const std::vector<std::shared_ptr<media::Media>> &, QSaveFile &);
};
}  // namespace memory
#endif
