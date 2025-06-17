#include "MainWindow.h"

#include <QVBoxLayout>

#include "DatabaseSelectionWidget.h"

namespace gui {
MainWindow::MainWindow(memory::Database &database, QWidget *parent,
                       Qt::WindowFlags flags)
    : QMainWindow(parent, flags),
      database_(database),
      stacked_widget_(this),
      central_widget_(new QFrame(this)),
      status_bar_(QStatusBar(this)) {
  stacked_widget_.addWidget(new DatabaseSelectionWidget(this));
  stacked_widget_.setAnimation(QEasingCurve::Type::OutQuart);
  stacked_widget_.setSpeed(450);

  auto *layout = new QVBoxLayout(this);
  central_widget_.setLayout(layout);

  layout->addWidget(&stacked_widget_);
  layout->addWidget(&status_bar_);

  setCentralWidget(&central_widget_);
}
}  // namespace gui
