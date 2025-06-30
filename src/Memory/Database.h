#ifndef MEMORY_DATABASE_H
#define MEMORY_DATABASE_H

#include <QString>
#include <memory>
#include <vector>

#include "./MediaContainer.h"

class QFile;

namespace media {
class Media;
}

namespace memory {

class Database {
 private:
  MediaContainer media_container_;
  QString file_path_;

  void fromJson(QFile& file);
  void fromXml(QFile& file);

 public:
  Database() = default;
  explicit Database(const QString& path);
  ~Database();

  bool open(const QString& path);
  bool close(bool save);  // salva se `save == true`
  bool save(const QString& path = QString());

  void addMedia(const media::Media& media);
  void removeMedia(const media::Media& media);
  void clear();

  std::vector<const media::Media*> getAll() const;
  std::vector<const media::Media*> filterMedia(const media::Media& filter) const;

  static const std::array<std::string, 2> kAcceptedExtensions;
};

}  // namespace memory

#endif  // MEMORY_DATABASE_H
