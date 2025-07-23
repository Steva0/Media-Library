#include <QApplication>
#include <iostream>

#include "./GUI/MainWindow.h"
#include "./Memory/Database.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  memory::Database database;
  gui::MainWindow main_window(database);
  QFile styleFile(":/assets/style.qss");
  styleFile.open(QFile::ReadOnly);
  app.setStyleSheet(styleFile.readAll());
  main_window.show();
  app.setActiveWindow(&main_window);
  return app.exec();
}
