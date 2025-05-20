#include "Database.h"

namespace memory {
DataBase::~DataBase() {
  // può darsi che se ne occupi il distruttore di QFile
  // comportamento di default: per ora metto che non vengono salvati i
  // cambiamenti
  close(false);
}
int DataBase::open(const QString &path) {
  // QFile.close() non lancia errori se il file non è stato aperto
  // file_.commit();
  file_.setFileName(path);
  if (!file_.open(QIODevice::ReadOnly | QIODevice::Text)) {
    // TODO(alessandro): possiamo creare una qualche enum per i codici di errore
    return 1;
  }
  return 0;
}
int DataBase::close(bool save_on_exit) {
  if (save_on_exit) {
    // ritorna false se c'è stato un errore. Possiamo voler cambiare il tipo di
    // ritorno del metodo.
    file_.commit();
  } else {
    // void cancelWriting()
    file_.cancelWriting();
  }
  return 0;
}

int DataBase::save() {
  // ritorna false in caso di fallimento
  if (!file_.commit()) {
    // errore in scrittura
    return -1;
  }
  // riapri il file dopo averlo chiuso
  // ritorna false in caso di fallimento
  if (!file_.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return 1;
  }
  return 0;
}

// qua possiamo volendo utilizzare riferimenti costanti al posto di puntatori
std::vector<media::Media *> DataBase::filterMedia(
    const media::Media *media_as_filter) {
  return media_container_.filter(media_as_filter);
}

}  // namespace memory
