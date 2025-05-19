#ifndef MEMORY_DATABASE_H
#define MEMORY_DATABASE_H
#include <QFile>

#include "./MediaContainer.h"

namespace memory {
class Database {
 private:
  MediaContainer media_container_;
  QFile db_file_;

 public:
  Database() = default;
  int open(const std::string &path);
  int close();
  int save();
  std::vector<media::Media *> filterMedia(const media::Media *) const;
};
}  // namespace memory
#endif
