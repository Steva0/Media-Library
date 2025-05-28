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

  class Deserializer {
    private:
     static std::vector<media::Media> fromJson(QFile &file);
     static std::vector<media::Media> fromXML(QFile &file);
    
   public:
    static std::vector<media::Media> deserialize(QFile &file);
  };

 public:
  Database(){};   //costruttore vuoto
  Database(const QString &path);  //costruttore partendo da un file

  ~Database();

  bool open(const QString &path);   //fa un clear e apre il file passato e lo assegna all'attributo file_
  bool close(bool save);  //se save == true, salva il database su file_ altrimenti fa solo un clear
  bool save();      //serializza il database su file_

  void addMedia(const media::Media &media); //aggiunge un media al database
  void removeMedia(const media::Media &media);  //rimuove un media dal database
  std::vector<const media::Media*> getAll() const;  //restituisce tutti i media del database
  void clear(); //svuota il database

  std::vector<const media::Media*> filterMedia(const media::Media &) const; //filtra i media del database in base al filtro passato come parametro
}; 
}  // namespace memory
#endif
