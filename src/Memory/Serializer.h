#ifndef MEMORY_SERIALIZER_H
#define MEMORY_SERIALIZER_H
#include <QFile>
#include "../Media/Media.h"

namespace memory {
class Serializer {
 private:
  static int vecToJSON(const std::vector<media::Media *> &, QFile &);
  static int vecToXML(const std::vector<media::Media *> &, QFile &);

 public:
  static int Serialize(const std::vector<media::Media *> &, QFile &);
};
}  // namespace memory
#endif
