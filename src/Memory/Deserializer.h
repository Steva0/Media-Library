#ifndef MEMORY_DESERIALIZER_H
#define MEMORY_DESERIALIZER_H
#include <QFile>

#include "../Media/Media.h"

namespace memory {
class Deserializer {
 private:
  static std::vector<std::shared_ptr<media::Media>>& XMLtoVec(const QFile &){}
  static std::vector<std::shared_ptr<media::Media>>& JSONtoVec(const QFile &){}

 public:
  static std::vector<std::shared_ptr<media::Media>>& deserialize(const QFile &){}
};
}  // namespace memory
#endif
