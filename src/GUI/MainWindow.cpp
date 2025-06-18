#include "MainWindow.h"

#include <QVBoxLayout>
#include <memory>

#include "DatabaseSelectionWidget.h"

//debug
#include "AdvancedSearch/AdvancedSearchResultVisitor.h"
#include "AdvancedSearch/AdvancedSearchResultsWidget.h"
#include "GUI/SlidingStackedWidget.h"

namespace gui {
const QString MainWindow::kConfigFileName = "config.txt";
const QString MainWindow::kDatabaseDirectory = "Database";

MainWindow::MainWindow(memory::Database &database, QWidget *parent,
                       Qt::WindowFlags flags)
    : QMainWindow(parent, flags),
      database_(database),
      stacked_widget_(new SlidingStackedWidget(this)),
      central_widget_(new QFrame(this)),
      status_bar_(new QStatusBar(this)) {
  recently_opened_ = std::make_unique<std::array<QString, 3>>();

  // leggi file contenente ultimi database aperti
  QFile recent_db(kConfigFileName);
  if (recent_db.open(QIODevice::Text | QFile::ReadOnly)) {
    QTextStream text_stream(&recent_db);

    for (size_t line = 0; line < 3; ++line) {
      if (!text_stream.readLineInto(&recently_opened_->at(line))) break;
    }
  }

  // fatta variabile a parte solo per rendere più comprensibile la parte della
  // connessione con segnali
  auto *db_selection_widget = new DatabaseSelectionWidget(this);
  stacked_widget_->addWidget(db_selection_widget);
  stacked_widget_->setAnimation(QEasingCurve::Type::OutQuart);
  stacked_widget_->setSpeed(450);

  auto *layout = new QVBoxLayout(central_widget_);

  layout->addWidget(stacked_widget_);
  layout->addWidget(status_bar_);

  setCentralWidget(central_widget_);

  // debug_visitor_advanced_search();

  connect(db_selection_widget, &DatabaseSelectionWidget::onPressRecent, this,
          &MainWindow::openRecent);
}

QString MainWindow::getRecentFilename(size_t number) const {
  if (number < recently_opened_->size()) {
    return recently_opened_->at(number);
  }
  return "";
}

void MainWindow::openRecent(size_t number) const {
  std::cout << "Sto aprendo: " << number << '\n';

  // qua viene creato un file anche se non esiste effettivamente
  // si tiene?
  if (number < recently_opened_->size() &&
      database_.open(recently_opened_->at(number))) {
    std::cerr << "Mostrare risultati apertura database\n";
  } else {
    std::cerr << "Errore di apertura oppure di implementazione in `number`\n";
  }
}

void MainWindow::closeDatabase(bool save) const {
  // bisogna aggiornare status line in base allo stato di chiusura del database
  database_.close(save);
}
std::vector<const media::Media *> MainWindow::filter(
    const media::Media &filter) const {
  return database_.filterMedia(filter);
}

void MainWindow::debug_visitor_advanced_search() {
  auto *media = new media::Album
  ("Nome Album", 2010, "IT",
        false, {"NomeGenere1", "Genere2"},
        ":/assets/matita.jpg", "Non dovrebbe essere visualizzato",
        "Nome band", {"Membro 1", "Membro 2", "Membro 3"},
        {"Canzone 1", "Canzone 2", "Canzone 3", "Canzone 4"});
  advanced_search::AdvancedSearchResultVisitor v;
  v.visit(*media);
  stacked_widget_->addWidget(v.getResult());
  stacked_widget_->setCurrentIndex(1);
}
}  // namespace gui
