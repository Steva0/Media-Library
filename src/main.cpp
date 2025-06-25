#include "./GUI/MainWindow.h"
#include "./Memory/Database.h"
#include <QApplication>

void debugDatabaseFileCreation(memory::Database &database) {
  database.open("database_test.xml");
  database.addMedia(
    media::Album("Album Test")
  );
  database.addMedia(
    media::Novel("Novel Test", 1234, "ASD", false, {"GenereGenere", "Generegenere"}, ":/assets/wifi.jpeg", "Za nooto", "Me", "Also me", 32, "Saaaaseries", "098")
  );
  database.addMedia(
    media::AudioBook("AudioBook Test", 10924, "Lingua", true, {"Genere1", "Genere2"}, "", "Note", "Nome Autore", "Nome editore", 2048, "Nome serie", "12345679857234-2", "Nome voce", "Nome Servizio streaming")
  );
  database.addMedia(
    media::Series("Series test", 123)
  );
  database.addMedia(
    media::Movie("Movie test")
  );
  database.addMedia(
    media::Ebook("Ebook test")
  );
  database.save();
}

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  memory::Database database;
  // debugDatabaseFileCreation(database);
  gui::MainWindow main_window(database);
  main_window.show();
  app.setActiveWindow(&main_window);
  return app.exec();
}
