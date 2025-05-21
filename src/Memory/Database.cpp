#include "Database.h"

#include <QFile>
#include <memory>

#include "Deserializer.h"
namespace memory {
Database::~Database() {
  close(false); // di default non salvare eventuali cambiamenti
}
bool Database::open(const QString &path) {
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return false;
  }
  // media_container_.addMedia(Deserializer::deserialize(file));
  file.close();
  return true;
}
bool Database::close(bool save_on_exit) {
  if (save_on_exit) {
    return file_.commit(); // false <=> errore
  }
  file_.cancelWriting();
  return true;
}

bool Database::save() {
  if (!file_.commit()) {
    // errore in scrittura
    return false;
  }
  
  if (!file_.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return false;
  }
  return true;
}

std::vector<const media::Media*> Database::filterMedia(
    const media::Media &media_as_filter) {
  return media_container_.filter(media_as_filter);
}

}  // namespace memory
