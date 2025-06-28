#include "MainWindow.h"

#include <QVBoxLayout>
#include <iostream>

#include "DatabaseSelectionWidget.h"

// debug
#include "AdvancedSearch/MainWidget.h"
#include "Search/SearchMain.h"
#include "PreviewVisitor.h"
#include "SlidingStackedWidget.h"

namespace gui {
MainWindow::MainWindow(memory::Database &database, QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags),
      database_(database),
      db_selection_widget_(new DatabaseSelectionWidget(this)),
      advanced_search_widget_(new advanced_search::MainWidget(this)),
      simple_search_widget_(new search::SearchMain(this)),
      stacked_widget_(new SlidingStackedWidget(this)),
      central_widget_(new QFrame(this)),
      status_bar_(new QStatusBar(this)),
      media_detail_page_(new MediaDetailPage(this)),
      media_edit_page_(new MediaEditPage(this)) {
  auto *status_wrapper = new QFrame(this);
  status_wrapper->setFrameShape(QFrame::Box);
  status_wrapper->setFrameShadow(QFrame::Shadow::Sunken);

  auto *status_layout = new QVBoxLayout(status_wrapper);
  status_layout->addWidget(status_bar_);
  status_layout->setContentsMargins(0, 0, 0, 0);

  stacked_widget_->setAnimation(QEasingCurve::Type::OutQuart);
  stacked_widget_->setSpeed(450);

  // db_selection_widget_ = new DatabaseSelectionWidget(this);
  stacked_widget_->addWidget(db_selection_widget_);

  // advanced_search_widget_ = new advanced_search::MainWidget(this);
  stacked_widget_->addWidget(advanced_search_widget_);

  stacked_widget_->addWidget(simple_search_widget_);

  stacked_widget_->addWidget(media_detail_page_);
  stacked_widget_->addWidget(media_edit_page_);

  auto *layout = new QVBoxLayout(central_widget_);

  layout->addWidget(stacked_widget_);
  layout->addWidget(status_wrapper);

  setCentralWidget(central_widget_);

  status_bar_->showMessage("Status bar.");

  // debugVisitorNormalSearch();
  // debugTimedEdit();
  // debugNormalSearch();

  showMaximized();

  connect(db_selection_widget_, &DatabaseSelectionWidget::onSelectDatabase, this, &MainWindow::accessDatabase);
  connect(advanced_search_widget_, &advanced_search::MainWidget::requestResults, this,
          &MainWindow::applyFilterAdvanced);
  connect(simple_search_widget_, &search::SearchMain::searchByName, this, &MainWindow::searchByName);
  // connect(this, &MainWindow::onQueryResults, advanced_search_widget,
  // &advanced_search::MainWidget::onGetSearchResults);

  // 1) Doppio click nella lista media -> apri dettaglio
  // ATTENZIONE: devi connettere il segnale corretto emesso da advanced_search_widget_
  // se esiste un segnale custom che fornisce il media selezionato.
  // Supponiamo che advanced_search_widget_ abbia il segnale:
  // void mediaDoubleClicked(const media::Media*);
  connect(advanced_search_widget_, &advanced_search::MainWidget::mediaDoubleClicked,
          this, &MainWindow::onMediaDoubleClicked);

  // 2) Segnali dal widget dettaglio per azioni
  connect(media_detail_page_, &MediaDetailPage::backRequested,
          this, &MainWindow::onBackFromDetail);

  connect(media_detail_page_, &MediaDetailPage::removeMediaRequested,
          this, &MainWindow::onRemoveMediaRequested);

  connect(media_detail_page_, &MediaDetailPage::enterEditRequested,
          this, &MainWindow::onEnterEditRequested);

  connect(media_edit_page_, &MediaEditPage::editConfirmed,
          this, &MainWindow::onEditConfirmed);

  connect(media_edit_page_, &MediaEditPage::backRequested,
          this, &MainWindow::onBackFromDetail);
  
  connect(media_edit_page_, &MediaEditPage::deleteRequested,
          this, &MainWindow::onRemoveMediaRequested);

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

void MainWindow::onMediaDoubleClicked(const media::Media *media) {
  if (!media)
    return;

  media_detail_page_->setMedia(media);
  stacked_widget_->setCurrentWidget(media_detail_page_);
}

// Slot per tornare indietro dalla pagina dettaglio
void MainWindow::onBackFromDetail() {
  stacked_widget_->setCurrentWidget(advanced_search_widget_);
}

// Slot per rimuovere media, chiamato da widget dettaglio
void MainWindow::onRemoveMediaRequested(const media::Media *media) {
  if (!media) {
    onBackFromDetail();
    return;
  }

  database_.removeMedia(*media);

  onBackFromDetail();

  media::Media* empty_filter = new media::Media("");  // Filtro vuoto per ricaricare tutti i media
  applyFilterAdvanced(empty_filter);
}

void MainWindow::onEnterEditRequested(const media::Media *Media) {
  if (!Media) {
    onBackFromDetail();
    return;
  }

  media_edit_page_->setMediaToEdit(Media);
  stacked_widget_->setCurrentWidget(media_edit_page_);

}

// Slot per modifica media, chiamato da widget dettaglio
void MainWindow::onEditConfirmed(const media::Media *newMedia, const media::Media *oldMedia) {
  if (!newMedia || !oldMedia || *newMedia == *oldMedia) {
    onBackFromDetail();
    return;
  }
  database_.removeMedia(*oldMedia);  // o un metodo update se ce l'hai
  database_.addMedia(*newMedia);
  onBackFromDetail();
  media::Media* empty_filter = new media::Media("");  // Filtro vuoto per ricaricare tutti i media
  applyFilterAdvanced(empty_filter);
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

void MainWindow::searchByName(const QString &title) {
  simple_search_widget_->acceptResults(database_.filterMedia(media::Media(title.toStdString())));
}

void MainWindow::debugVisitorNormalSearch() {
  PreviewVisitor v;
  auto *album = new media::Album("Nome Album", 2010, "IT", false, {"NomeGenere1", "Genere2"}, ":/assets/matita.jpg",
                                 "Non dovrebbe essere visualizzato", "Nome band", {"Membro 1", "Membro 2", "Membro 3"},
                                 {"Canzone 1", "Canzone 2", "Canzone 3", "Canzone 4"});
  album->accept(v);
  QWidget *widget = v.getWidget();
  widget->setParent(this);
  stacked_widget_->addWidget(widget);
  stacked_widget_->setCurrentIndex(stacked_widget_->count() - 1);
}
void MainWindow::debugTimedEdit() {
  auto *timed_line = new search::InputBar(this);
  stacked_widget_->addWidget(timed_line);
  stacked_widget_->setCurrentIndex(stacked_widget_->count() - 1);
  connect(timed_line, &search::InputBar::timedEdit, this, [](const QString &text){std::cout << text.toStdString() << '\n'; });
}
void MainWindow::debugNormalSearch() {
  auto *search = new search::SearchMain(this);
  stacked_widget_->addWidget(search);
  stacked_widget_->setCurrentIndex(stacked_widget_->count() - 1);
}
}  // namespace gui
