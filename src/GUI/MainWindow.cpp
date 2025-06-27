#include "MainWindow.h"

#include <QVBoxLayout>

#include "DatabaseSelectionWidget.h"

// debug
#include "AdvancedSearch/InputWidget.h"
#include "AdvancedSearch/MainWidget.h"
#include "AdvancedSearch/ResultsWidget.h"
#include "./PreviewVisitor.h"
#include "SlidingStackedWidget.h"

namespace gui {
MainWindow::MainWindow(memory::Database &database, QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags),
      database_(database),
      stacked_widget_(new SlidingStackedWidget(this)),
      central_widget_(new QFrame(this)),
      status_bar_(new QStatusBar(this)) {
  auto *status_wrapper = new QFrame(this);
  status_wrapper->setFrameShape(QFrame::Box);
  status_wrapper->setFrameShadow(QFrame::Shadow::Sunken);

  auto *status_layout = new QVBoxLayout(status_wrapper);
  status_layout->addWidget(status_bar_);
  status_layout->setContentsMargins(0, 0, 0, 0);

  stacked_widget_->setAnimation(QEasingCurve::Type::OutQuart);
  stacked_widget_->setSpeed(450);

  db_selection_widget_ = new DatabaseSelectionWidget(this);
  stacked_widget_->addWidget(db_selection_widget_);

  advanced_search_widget_ = new advanced_search::MainWidget(this);
  stacked_widget_->addWidget(advanced_search_widget_);

  auto *layout = new QVBoxLayout(central_widget_);

  layout->addWidget(stacked_widget_);
  layout->addWidget(status_wrapper);

  setCentralWidget(central_widget_);

  status_bar_->showMessage("Status bar.");

  // debugVisitorAdvancedSearch();
  // debugShowAdvancedSearchResults();
  // debugShowAdvancedSearchInput();
  // debugShowAdvancedSearchMainWidget();
  debugVisitorNormalSearch();

  connect(db_selection_widget_, &DatabaseSelectionWidget::onSelectDatabase, this, &MainWindow::accessDatabase);
  connect(advanced_search_widget_, &advanced_search::MainWidget::requestResults, this,
          &MainWindow::applyFilterAdvanced);
  // connect(this, &MainWindow::onQueryResults, advanced_search_widget,
  // &advanced_search::MainWidget::onGetSearchResults);

  // debug
  auto *next = new QPushButton("Next", this);
  auto *prev = new QPushButton("prev", this);

  layout->addWidget(next);
  layout->addWidget(prev);
  connect(next, &QAbstractButton::clicked,
          [&]() { stacked_widget_->setCurrentIndex(stacked_widget_->currentIndex() + 1); });
  connect(prev, &QAbstractButton::clicked,
          [&]() { stacked_widget_->setCurrentIndex(stacked_widget_->currentIndex() - 1); });
}

void MainWindow::accessDatabase(const QString &path) {
  database_.open(path);
  // temp
  stacked_widget_->setCurrentIndex(1);
}

void MainWindow::closeDatabase(bool save) {
  // bisogna aggiornare status line in base allo stato di chiusura del database
  database_.close(save);
}

void MainWindow::applyFilterAdvanced(const media::Media *filter) {
  advanced_search_widget_->updateResults(database_.filterMedia(*filter));
  delete filter;
}

void MainWindow::debugVisitorNormalSearch() {
  search::PreviewVisitor v;
  auto *album = new media::Album("Nome Album", 2010, "IT", false, {"NomeGenere1", "Genere2"}, ":/assets/matita.jpg",
                                 "Non dovrebbe essere visualizzato", "Nome band", {"Membro 1", "Membro 2", "Membro 3"},
                                 {"Canzone 1", "Canzone 2", "Canzone 3", "Canzone 4"});
  album->accept(v);
  QWidget *widget = v.getResult();
  widget->setParent(this);
  stacked_widget_->addWidget(widget);
  stacked_widget_->setCurrentIndex(stacked_widget_->count() - 1);
}
}  // namespace gui
