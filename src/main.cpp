#include "./GUI/MainWindow.h"
#include "./Memory/Database.h"
#include <QApplication>

void debug_database_file_creation(memory::Database &database) {
  database.open("database_test.json");
  database.addMedia(
    media::Album("Album Test")
  );
  database.addMedia(
    media::Novel("Novel Test")
  );
  database.save();
}

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  memory::Database database;
  debug_database_file_creation(database);
  gui::MainWindow main_window(database);
  main_window.show();
  app.setActiveWindow(&main_window);
  return app.exec();
}
