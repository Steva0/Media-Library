#ifndef MEMORY_DESERIALIZER_H
#define MEMORY_DESERIALIZER_H
#include <QFile>

#include "../Media/Media.h"

namespace memory {
class Deserializer {
 private:
  static std::vector<media::Media *>& XMLtoVec(const QFile &);
  static std::vector<media::Media *>& JSONtoVec(const QFile &);

 public:
  static std::vector<media::Media *>& deserialize(const QFile &);
};
}  // namespace memory
#endif
