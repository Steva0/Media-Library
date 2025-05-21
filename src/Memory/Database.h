#ifndef MEMORY_DATABASE_H
#define MEMORY_DATABASE_H
#include <QSaveFile>

#include "./MediaContainer.h"
#include <memory>

namespace memory {
class Database {
 private:
  MediaContainer media_container_;
  QSaveFile file_;

 public:
  ~Database();

  bool open(const QString &path);
  bool close(bool save);
  bool save();

  std::vector<std::shared_ptr<media::Media>> filterMedia(const media::Media &);
};
}  // namespace memory
#endif
