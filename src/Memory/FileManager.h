#ifndef MEMORY_FILE_MANAGER_H
#define MEMORY_FILE_MANAGER_H

#include <QString>
#include <memory>
#include <vector>

class QFile;

namespace media {
class Media;
}

namespace memory {
class Database;

class FileManager {
 private:
  QString file_path_;

  std::vector<std::unique_ptr<media::Media>> fromJson(QFile& file);
  std::vector<std::unique_ptr<media::Media>> fromXml(QFile& file);

 public:
  FileManager() = default;
  explicit FileManager(const QString& path);
  ~FileManager();

  std::vector<std::unique_ptr<media::Media>> deserialize(const QString& path);
  void close();                                                   // chiudi senza salvare
  bool close(const std::vector<const media::Media*>& save_data);  // chiudi dopo aver salvato
  // bool save(const QString& path = QString());
  bool save(const std::vector<const media::Media*>& data, const QString& path = "");

  static const std::array<std::string, 2> kAcceptedExtensions;
};

}  // namespace memory

#endif  // MEMORY_DATABASE_H
