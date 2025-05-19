#ifndef MEMORY_DATABASE_H
#define MEMORY_DATABASE_H
#include <QSaveFile>

#include "./MediaContainer.h"

namespace memory {
class DataBase {
 private:
  MediaContainer media_container_;
  QSaveFile file_;

  // possiamo mettere open, close e save privati e poi usare un tipo di observer
  // pattern per chiamare le funzioni.
 public:
  DataBase() = default;
  ~DataBase();
  int open(const QString &path);
  int close(bool save);
  int save();
  // TODO(alessandro): smart pointer
  // possiamo cambiarlo a riferimenti costanti
  std::vector<media::Media *> filterMedia(const media::Media *);
};
}  // namespace memory
#endif
