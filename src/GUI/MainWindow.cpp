#include "MainWindow.h"
#include "DatabaseSelectionWidget.h"

namespace gui {
MainWindow::MainWindow(memory::Database &database, QWidget *parent,
                       Qt::WindowFlags flags)
    : QMainWindow(parent, flags), database_(database), stacked_widget_(this) {
  stacked_widget_.addWidget(new DatabaseSelectionWidget(this));
  stacked_widget_.setAnimation(QEasingCurve::Type::OutQuart);
  stacked_widget_.setSpeed(450);
  setCentralWidget(&stacked_widget_);
}
} // namespace gui
