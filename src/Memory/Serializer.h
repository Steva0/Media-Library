#ifndef MEMORY_SERIALIZER_H
#define MEMORY_SERIALIZER_H
#include <QSaveFile>
#include "../Media/Media.h"

namespace memory {
class Serializer {

 private:
  static int vecToJSON(const media::Media &, QSaveFile &){}
  static int vecToXML(const media::Media&, QSaveFile &){}

 public:
  static int Serialize(std::vector<const media::Media*>, QSaveFile &){}
};
}  // namespace memory
#endif
