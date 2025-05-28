#include "Database.h"

#include <QFile>
#include <memory>

namespace memory {
Database::~Database() {
  close(false); // di default non salvare eventuali cambiamenti
}
Database::Database(const QString &path) : file_(path) {
  if (!file_.open(QIODevice::ReadWrite | QIODevice::Text)) {
    // errore apertura file
    return;
  }
  // media_container_.addMedia(Deserializer::deserialize(file_));
}

bool Database::open(const QString &path) {
  if (path == file_.fileName()) { //da vedere come sono scritti i nomi dei file, se con o senza percorso se il file finisce in .tmp non funziona esempio
    // il file è già aperto
    return true;
  }
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return false;
  }
  media_container_.clear(); // svuota il database corrente
  // media_container_.addMedia(Deserializer::deserialize(file));
  file.close();
  return true;
}

bool Database::close(bool save_on_exit) {
  if (save_on_exit) {
    media_container_.serialize(file_);
    return file_.commit(); // false <=> errore
  }
  file_.cancelWriting();
  return true;
}

bool Database::save() {
  media_container_.serialize(file_);
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
    const media::Media &media_as_filter) const {
  return media_container_.filter(media_as_filter);
}

void Database::addMedia(const media::Media &media) {
    media_container_.addMedia(media);
}

void Database::removeMedia(const media::Media &media) {
  media_container_.removeMedia(media);
}

void Database::clear(){
  media_container_.clear();
}

std::vector<const media::Media*> Database::getAll() const {
  return media_container_.getAll();
}
}  // namespace memory
