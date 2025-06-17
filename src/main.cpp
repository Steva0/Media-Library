#include "./GUI/MainWindow.h"
#include "./Memory/Database.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  memory::Database database;
  gui::MainWindow main_window(database);
  main_window.show();
  app.setActiveWindow(&main_window);
  return app.exec();
}
