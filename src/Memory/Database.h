#ifndef MEMORY_DATABASE_H
#define MEMORY_DATABASE_H

#include <QFile>
#include <array>
#include <memory>
#include <vector>

#include "../Media/Media.h"
#include "FileManager.h"
#include "Serializer.h"

namespace memory {
class Database {
  friend class MediaTypeVisitor;

 public:
  enum class Type { All = 0, Novel, Album, Movie, Ebook, AudioBook, Series, TypeCount };

  static std::string typeToString(Type);
  static std::string typeToString(size_t);
  static const std::array<std::string, static_cast<size_t>(Type::TypeCount)> kTypeStrings;

  const media::Media *addMedia(const media::Media &);
  void removeMedia(const media::Media &media);
  void clear();

  void open(const QString &path);
  void save();
  void close(bool changes);

  std::vector<const media::Media *> filter(const media::Media &media) const;
  std::vector<const media::Media *> getAll() const;

 private:
  int serializeAll(QFile &file) const;

  FileManager file_manager_;
  std::vector<std::unique_ptr<media::Media>> data_;
};

}  // namespace memory

#endif  // MEMORY_MEDIACONTAINER_H
