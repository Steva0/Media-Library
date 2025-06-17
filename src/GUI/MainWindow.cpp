#include "MainWindow.h"

#include <QVBoxLayout>
#include <memory>

#include "DatabaseSelectionWidget.h"

namespace gui {
const QString MainWindow::kConfigFileName = "config.txt";
const QString MainWindow::kDatabaseDirectory = "Database";

MainWindow::MainWindow(memory::Database &database, QWidget *parent,
                       Qt::WindowFlags flags)
    : QMainWindow(parent, flags),
      database_(database),
      stacked_widget_(this),
      central_widget_(new QFrame(this)),
      status_bar_(QStatusBar(this)) {
  recently_opened_ = std::make_unique<std::array<QString, 3>>();

  // leggi file contenente ultimi database aperti
  QFile recent_db(kConfigFileName);
  if (recent_db.open(QIODevice::Text | QFile::ReadOnly)) {
    QTextStream text_stream(&recent_db);

    for (size_t line = 0; line < 3; ++line) {
      if (!text_stream.readLineInto(&recently_opened_->at(line))) break;
    }
  }

  stacked_widget_.addWidget(new DatabaseSelectionWidget(this));
  stacked_widget_.setAnimation(QEasingCurve::Type::OutQuart);
  stacked_widget_.setSpeed(450);

  auto *layout = new QVBoxLayout;
  central_widget_.setLayout(layout);

  layout->addWidget(&stacked_widget_);
  layout->addWidget(&status_bar_);

  setCentralWidget(&central_widget_);
}

QString MainWindow::getRecentFilename(size_t number) const {
  if (number < recently_opened_->size()) {
    return recently_opened_->at(number);
  }
  return "";
}

bool MainWindow::openRecent(size_t number) const {
  if (number < recently_opened_->size()) {
    return database_.open(recently_opened_->at(number));
  }
  return false;
}

bool MainWindow::closeDatabase(bool save) const {
  return database_.close(save);
}
}  // namespace gui
