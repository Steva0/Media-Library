#include "MainWindow.h"

#include <QVBoxLayout>
#include <memory>

#include "DatabaseSelectionWidget.h"

// debug
#include "AdvancedSearch/InputWidget.h"
#include "AdvancedSearch/ResultVisitor.h"
#include "AdvancedSearch/ResultsWidget.h"
#include "AdvancedSearch/MainWidget.h"
#include "GUI/SlidingStackedWidget.h"

namespace gui {
MainWindow::MainWindow(memory::Database &database, QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags),
      database_(database),
      stacked_widget_(new SlidingStackedWidget(this)),
      central_widget_(new QFrame(this)),
      status_bar_(new QStatusBar(this)) {
  stacked_widget_->setAnimation(QEasingCurve::Type::OutQuart);
  stacked_widget_->setSpeed(450);

  auto *db_selection_widget = new DatabaseSelectionWidget(this);
  stacked_widget_->addWidget(db_selection_widget);

  // auto *advanced_search_widget = new advanced_search::MainWidget(this);
  // stacked_widget_->addWidget(advanced_search_widget);

  auto *layout = new QVBoxLayout(central_widget_);

  layout->addWidget(stacked_widget_);
  layout->addWidget(status_bar_);

  setCentralWidget(central_widget_);

  // debugVisitorAdvancedSearch();
  // debugShowAdvancedSearchResults();
  // debugShowAdvancedSearchInput();
}

void MainWindow::openDatabase(const QString &path) const {
  database_.open(path);
}

void MainWindow::closeDatabase(bool save) const {
  // bisogna aggiornare status line in base allo stato di chiusura del database
  database_.close(save);
}

std::vector<const media::Media *> MainWindow::filter(const media::Media &filter) const {
  return database_.filterMedia(filter);
}

void MainWindow::debugVisitorAdvancedSearch() {
  auto *media = new media::Album("Nome Album", 2010, "IT", false, {"NomeGenere1", "Genere2"}, ":/assets/matita.jpg",
                                 "Non dovrebbe essere visualizzato", "Nome band", {"Membro 1", "Membro 2", "Membro 3"},
                                 {"Canzone 1", "Canzone 2", "Canzone 3", "Canzone 4"});
  advanced_search::ResultVisitor v;
  v.visit(*media);
  stacked_widget_->addWidget(v.getResult());
  stacked_widget_->setCurrentIndex(1);
}
void MainWindow::debugShowAdvancedSearchResults() {
  auto *results_widget = new advanced_search::ResultsWidget(this);
  stacked_widget_->addWidget(results_widget);
  // results_widget->search<media::Media>(media::Media(""));
  results_widget->search(media::Novel(""));
  stacked_widget_->setCurrentIndex(1);
}

void MainWindow::debugShowAdvancedSearchInput() {
  auto *input_widget = new advanced_search::InputWidget(this);
  stacked_widget_->addWidget(input_widget);
  stacked_widget_->setCurrentIndex(1);
}
}  // namespace gui
