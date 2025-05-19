#ifndef MEMORY_SERIALIZER_H
#define MEMORY_SERIALIZER_H
#include <QFile>

#include "../Media/Media.h"

namespace memory {
class Serializer {
 private:
  static std::vector<media::Media *>& XMLtoVec(const QFile &);
  static std::vector<media::Media *>& JSONtoVec(const QFile &);

 public:
  static std::vector<media::Media *>& serialize(const QFile &);
};
}  // namespace memory
#endif
