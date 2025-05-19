#ifndef MEMORY_DESERIALIZER_H
#define MEMORY_DESERIALIZER_H
#include <QFile>
#include "../Media/Media.h"

namespace memory {
class Deserializer {
 private:
  static int vecToJSON(const std::vector<media::Media *> &, QFile &);
  static int vecToXML(const std::vector<media::Media *> &, QFile &);

 public:
  static int deserialize(const std::vector<media::Media *> &, QFile &);
};
}  // namespace memory
#endif
