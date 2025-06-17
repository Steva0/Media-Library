#ifndef GRAPHICS_MAIN_WINDOW_H
#define GRAPHICS_MAIN_WINDOW_H
#include "../Memory/Database.h"
#include "SlidingStackedWidget.h"
#include <QMainWindow>
#include <QStatusBar>
#include <QFrame>

namespace gui {
class MainWindow : public QMainWindow {
  Q_OBJECT
private:
  memory::Database &database_;
  SlidingStackedWidget stacked_widget_;
  QFrame central_widget_;
  QStatusBar status_bar_;

public:
  explicit MainWindow(memory::Database &database, QWidget *parent = nullptr,
                      Qt::WindowFlags flags = Qt::WindowFlags());
};
} // namespace gui
#endif
