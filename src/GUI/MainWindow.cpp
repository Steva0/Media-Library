#include "MainWindow.h"

#include <QVBoxLayout>
#include <iostream>

#include "DatabaseSelectionWidget.h"

// debug
#include "AdvancedSearch/MainWidget.h"
#include "PreviewVisitor.h"
#include "Search/SearchMain.h"
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
      media_edit_page_(new MediaEditPage(this)),
      add_media_view_page_(new AddMediaViewPage(this)){
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
  stacked_widget_->addWidget(add_media_view_page_);

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
  connect(simple_search_widget_, &search::SearchMain::mediaDoubleClicked, this, &MainWindow::onMediaDoubleClicked);
  connect(simple_search_widget_, &search::SearchMain::requestEdit, this, &MainWindow::onEnterEditRequested);
  connect(simple_search_widget_, &search::SearchMain::requestDelete, this, &MainWindow::onRemoveMediaRequested);

  // connect(this, &MainWindow::onQueryResults, advanced_search_widget,
  // &advanced_search::MainWidget::onGetSearchResults);

  // 1) Doppio click nella lista media -> apri dettaglio
  // ATTENZIONE: devi connettere il segnale corretto emesso da advanced_search_widget_
  // se esiste un segnale custom che fornisce il media selezionato.
  // Supponiamo che advanced_search_widget_ abbia il segnale:
  // void mediaDoubleClicked(const media::Media*);
  connect(advanced_search_widget_, &advanced_search::MainWidget::mediaDoubleClicked, this,
          &MainWindow::onMediaDoubleClicked);
  connect(advanced_search_widget_, &advanced_search::MainWidget::backRequested, this,
          [this]() { navigateTo(simple_search_widget_); });

  // 2) Segnali dal widget dettaglio per azioni
  connect(media_detail_page_, &MediaDetailPage::backRequested, this, &MainWindow::goBack);
  connect(media_detail_page_, &MediaDetailPage::removeMediaRequested, this, &MainWindow::onRemoveMediaRequested);
  connect(media_detail_page_, &MediaDetailPage::removeMediaRequested, [this]() { navigateTo(current_search_widget_); });
  connect(media_detail_page_, &MediaDetailPage::removeMediaRequested, simple_search_widget_, &search::SearchMain::hidePreview);
  connect(media_detail_page_, &MediaDetailPage::enterEditRequested, this, &MainWindow::onEnterEditRequested);

  connect(media_edit_page_, &MediaEditPage::editConfirmed,
          [this](const media::Media *new_media, const media::Media *old_media) {
            onEditConfirmed(new_media, old_media);
          });
  connect(media_edit_page_, &MediaEditPage::editConfirmed, [this]() { navigateTo(current_search_widget_); });
  connect(media_edit_page_, &MediaEditPage::editConfirmed, simple_search_widget_, &search::SearchMain::hidePreview);
  connect(media_edit_page_, &MediaEditPage::backRequested, this, &MainWindow::goBack);
  connect(media_edit_page_, &MediaEditPage::deleteRequested, this, &MainWindow::onRemoveMediaRequested);
  connect(media_edit_page_, &MediaEditPage::deleteRequested, simple_search_widget_, &search::SearchMain::hidePreview);
  connect(media_edit_page_, &MediaEditPage::deleteRequested, [this]() { navigateTo(current_search_widget_); });

  connect(simple_search_widget_, &search::SearchMain::advancedClicked, this,
          [&]() { navigateTo(advanced_search_widget_); });
  connect(simple_search_widget_, &search::SearchMain::commitEditChanges,
          [this](const media::Media *new_media, const media::Media *old_media) {
            onEditConfirmed(new_media, old_media);
          });
  connect(simple_search_widget_, &search::SearchMain::addNewMedia, this,
          [&]() { navigateTo(add_media_view_page_); });
  connect(add_media_view_page_, &AddMediaViewPage::mediaAdded, this, &MainWindow::onAddMedia);
  connect(add_media_view_page_, &AddMediaViewPage::backRequested, this,
          [&]() { navigateTo(current_search_widget_); });
}

void MainWindow::onMediaDoubleClicked(const media::Media *media) {
  if (!media) return;

  media_detail_page_->setMedia(media);
  navigateTo(media_detail_page_);
}

// Slot per tornare indietro dalla pagina dettaglio
void MainWindow::goBack() {
  if (!navigation_stack_.empty()) {
    QWidget *previous = navigation_stack_.top();
    navigation_stack_.pop();
    stacked_widget_->setCurrentWidget(previous);
  }
}

// Slot per rimuovere media, chiamato da widget dettaglio
void MainWindow::onRemoveMediaRequested(const media::Media *media) {
  if (!media) {
    goBack();
    return;
  }

  database_.removeMedia(*media);

  media::Media *empty_filter = new media::Media("");  // Filtro vuoto per ricaricare tutti i media
  applyFilterAdvanced(empty_filter);

  // Aggiorna ricerca semplice
  simple_search_widget_->acceptResults(database_.filterMedia(media::Media(last_simple_search_query_.toStdString())));
}

void MainWindow::onAddMedia(media::Media *newMedia) {
  if (!newMedia) {
    std::cout << "Nuovo media non valido, non aggiunto al database.\n";
    return;
  }

  // Aggiungi il nuovo media al database
  database_.addMedia(*newMedia);

  // Aggiorna i risultati della ricerca (avanzata) per riflettere il nuovo media
  media::Media *empty_filter = new media::Media("");  // filtro vuoto = tutti i media
  applyFilterAdvanced(empty_filter);

  // Aggiorna ricerca semplice
  simple_search_widget_->acceptResults(database_.filterMedia(media::Media(last_simple_search_query_.toStdString())));

  // Naviga alla pagina di dettaglio del nuovo media
  media_detail_page_->setMedia(newMedia);
  navigateTo(media_detail_page_);
}

void MainWindow::onEnterEditRequested(const media::Media *Media) {
  if (!Media) {
    goBack();
    return;
  }

  media_edit_page_->setMediaToEdit(Media);
  navigateTo(media_edit_page_);
}

// Slot per modifica media, chiamato da widget dettaglio
void MainWindow::onEditConfirmed(const media::Media *newMedia, const media::Media *oldMedia) {
  if (!newMedia || !oldMedia || *newMedia == *oldMedia) {
    goBack();
    return;
  }

  database_.removeMedia(*oldMedia);
  database_.addMedia(*newMedia);

  // Aggiorna la pagina dettaglio con il nuovo media
  media_detail_page_->setMedia(newMedia);

  // Aggiorna i risultati della ricerca (avanzata) per riflettere il cambiamento
  media::Media *empty_filter = new media::Media("");
  applyFilterAdvanced(empty_filter);

  // Aggiorna ricerca semplice
  simple_search_widget_->acceptResults(database_.filterMedia(media::Media(last_simple_search_query_.toStdString())));
}

void MainWindow::accessDatabase(const QString &path) {
  database_.open(path);

  // Appena aperto il db, aggiorna i risultati di ricerca con tutti i media o con filtro vuoto
  media::Media *empty_filter = new media::Media("");  // filtro vuoto = tutti i media
  applyFilterAdvanced(empty_filter);

  // Aggiorna anche la ricerca semplice con titolo vuoto per mostrare tutti i media
  last_simple_search_query_ = "";
  simple_search_widget_->acceptResults(database_.filterMedia(media::Media("")));

  // Naviga alla schermata principale di ricerca avanzata (o altra)
  navigateTo(simple_search_widget_);
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
  last_simple_search_query_ = title;
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
  connect(timed_line, &search::InputBar::timedEdit, this,
          [](const QString &text) { std::cout << text.toStdString() << '\n'; });
}
void MainWindow::debugNormalSearch() {
  auto *search = new search::SearchMain(this);
  stacked_widget_->addWidget(search);
  stacked_widget_->setCurrentIndex(stacked_widget_->count() - 1);
}
void MainWindow::navigateTo(QWidget *next_page) {
  QWidget *current = stacked_widget_->currentWidget();
  if (current && current != next_page) {
    navigation_stack_.push(current);
  }
  if (dynamic_cast<advanced_search::MainWidget*>(next_page) || dynamic_cast<search::SearchMain *>(next_page))
    current_search_widget_ = next_page;
  stacked_widget_->setCurrentWidget(next_page);
}

}  // namespace gui
