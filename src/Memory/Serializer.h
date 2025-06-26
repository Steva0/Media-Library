#ifndef MEMORY_SERIALIZER_H
#define MEMORY_SERIALIZER_H

#include <QFile>
#include <vector>

namespace media {
class Media;
}

namespace memory {

class Serializer {
 public:
  // Restituisce:
  //  0  -> successo
  // -1 -> errore apertura file
  // -2 -> errore scrittura file
  static int serialize(const std::vector<const media::Media*>& mediaList, QFile& file);
};

}  // namespace memory

#endif  // MEMORY_SERIALIZER_H
