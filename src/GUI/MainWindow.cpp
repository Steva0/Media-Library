#include "MainWindow.h"

#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QVBoxLayout>
#include <algorithm>
#include <cctype>
#include <iostream>

#include "DatabaseSelectionWidget.h"

// debug
#include "AbstractSearchWidget.h"
#include "AdvancedSearch/MainWidget.h"
#include "PreviewVisitor.h"
#include "Search/SearchMain.h"
#include "SlidingStackedWidget.h"
#include "qmessagebox.h"

namespace gui {

MainWindow::MainWindow(memory::Database &database, QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags),
      database_(database),
      changes_were_made_(false),
      db_selection_widget_(new DatabaseSelectionWidget(this)),
      advanced_search_widget_(new advanced_search::MainWidget(this)),
      simple_search_widget_(new search::SearchMain(this)),
      stacked_widget_(new SlidingStackedWidget(this)),
      central_widget_(new QFrame(this)),
      status_bar_(new QStatusBar(this)),
      media_detail_page_(new MediaDetailPage(this)),
      media_edit_page_(new MediaEditPage(this)),
      add_media_view_page_(new AddMediaViewPage(this)) {
  setWindowTitle("Media Library");
  std::vector<QString> filetypes{};
  std::for_each(memory::Database::kAcceptedExtensions.begin(), memory::Database::kAcceptedExtensions.end(),
                [&filetypes](const std::string &type) { filetypes.push_back(QString::fromStdString(type).toUpper()); });
  for (size_t i = 0; i < filetypes.size(); ++i) {
    allowed_filter_ +=
        filetypes[i] + QString(" files (*.") + QString::fromStdString(memory::Database::kAcceptedExtensions[i]) + ");;";
  }

  auto *status_wrapper = new QFrame(this);
  status_wrapper->setFrameShape(QFrame::Box);
  status_wrapper->setFrameShadow(QFrame::Shadow::Sunken);

  auto *status_layout = new QVBoxLayout(status_wrapper);
  status_layout->addWidget(status_bar_);
  status_layout->setContentsMargins(0, 0, 0, 0);

  stacked_widget_->setAnimation(QEasingCurve::Type::OutQuart);
  stacked_widget_->setSpeed(450);

  stacked_widget_->addWidget(db_selection_widget_);
  stacked_widget_->addWidget(advanced_search_widget_);
  stacked_widget_->addWidget(simple_search_widget_);
  stacked_widget_->addWidget(media_detail_page_);
  stacked_widget_->addWidget(media_edit_page_);
  stacked_widget_->addWidget(add_media_view_page_);

  auto *layout = new QVBoxLayout(central_widget_);

  layout->addWidget(stacked_widget_);
  layout->addWidget(status_wrapper);

  setCentralWidget(central_widget_);

  auto *open_db = new QAction("Apri", this);
  auto *new_db = new QAction("Nuovo", this);
  auto *close_db = new QAction("Chiudi", this);
  auto *save_db = new QAction("Salva", this);

  menu_ = menuBar()->addMenu("&Database");

  menu_->addAction(save_db);
  menu_->addAction(new_db);
  menu_->addAction(open_db);
  menu_->addAction(close_db);

  menuBar()->hide();

  showMaximized();

  connect(save_db, &QAction::triggered, this, &MainWindow::saveDatabase);
  connect(new_db, &QAction::triggered, this, &MainWindow::createDatabase);
  connect(open_db, &QAction::triggered, this, &MainWindow::openDatabase);
  connect(close_db, &QAction::triggered, this, &MainWindow::closeDatabase);  // da sistemare

  connect(db_selection_widget_, &DatabaseSelectionWidget::onSelectDatabase, this, &MainWindow::openDatabase);
  connect(db_selection_widget_, &DatabaseSelectionWidget::onCreateDatabase, this, &MainWindow::createDatabase);
  connect(advanced_search_widget_, &advanced_search::MainWidget::requestResults, this,
          &MainWindow::applyFilterAdvanced);
  connect(simple_search_widget_, &AbstractSearchWidget::requestResults, this, &MainWindow::simpleSearch);
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
  connect(media_detail_page_, &MediaDetailPage::removeMediaRequested, simple_search_widget_,
          &search::SearchMain::hidePreview);
  connect(media_detail_page_, &MediaDetailPage::enterEditRequested, this, &MainWindow::onEnterEditRequested);

  connect(
      media_edit_page_, &MediaEditPage::editConfirmed,
      [this](const media::Media *new_media, const media::Media *old_media) { onEditConfirmed(new_media, old_media); });
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
            if (!(*new_media == *old_media)) onEditConfirmed(new_media, old_media);
          });
  connect(simple_search_widget_, &search::SearchMain::addNewMedia, this, [&]() {
    add_media_view_page_->clearEditSection();
    navigateTo(add_media_view_page_);
  });
  connect(add_media_view_page_, &AddMediaViewPage::mediaAdded, this, &MainWindow::onAddMedia);
  connect(add_media_view_page_, &AddMediaViewPage::backRequested, this, [&]() {
    add_media_view_page_->clearEditSection();
    navigateTo(current_search_widget_);
  });
}

void MainWindow::createDatabase() {
  if (savePopup()) database_.save();
  QString filter;
  QString path = QFileDialog::getSaveFileName(this, "New Database", ".", allowed_filter_, &filter);
  if (path == "") return;

  if (filter.contains("xml"))
    filter = ".xml";
  else
    filter = ".json";

  if (!path.endsWith(filter)) path += filter;

  accessDatabase(path);
  database_.clear();

  // media::Media *empty_filter = new media::Media("");  // filtro vuoto = tutti i media
  applyFilterAdvanced(media::Media{});

  // Aggiorna anche la ricerca semplice con titolo vuoto per mostrare tutti i media
  last_simple_search_query_ = "";
  // simple_search_widget_->acceptResults(database_.filterMedia(media::Media("")));
  simple_search_widget_->updateResults(database_.filterMedia(media::Media{}));

  status_bar_->showMessage("Creato database: " + path);
}

void MainWindow::openDatabase() {
  if (savePopup()) database_.save();
  QString path = QFileDialog::getOpenFileName(nullptr, "Open Database", ".", allowed_filter_);
  if (path == "") return;  // "cancel"
  accessDatabase(path);
  //
  // Appena aperto il db, aggiorna i risultati di ricerca con tutti i media o con filtro vuoto
  // media::Media *empty_filter = new media::Media("");  // filtro vuoto = tutti i media
  applyFilterAdvanced(media::Media{});

  // Aggiorna anche la ricerca semplice con titolo vuoto per mostrare tutti i media
  last_simple_search_query_ = "";
  // simple_search_widget_->acceptResults(database_.filterMedia(media::Media("")));
  simple_search_widget_->updateResults(database_.filterMedia(media::Media{}));
  status_bar_->showMessage(QString("Caricato database") + path);
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
    // stacked_widget_->setCurrentWidget(previous);
    stacked_widget_->slideInWgt(previous);
    if (previous == simple_search_widget_) menuBar()->show();
  }
}

// Slot per rimuovere media, chiamato da widget dettaglio
void MainWindow::onRemoveMediaRequested(const media::Media *media) {
  if (!media) {
    goBack();
    return;
  }

  status_bar_->showMessage("Cancellando media: " + QString::fromStdString(media->getTitle()));
  database_.removeMedia(*media);

  changes_were_made_ = true;

  // media::Media *empty_filter = new media::Media("");  // Filtro vuoto per ricaricare tutti i media
  applyFilterAdvanced(media::Media{});

  // Aggiorna ricerca semplice
  // simple_search_widget_->acceptResults(database_.filterMedia(media::Media(last_simple_search_query_.toStdString())));
  simple_search_widget_->updateResults(database_.filterMedia(media::Media(last_simple_search_query_.toStdString())));
}

void MainWindow::onAddMedia(media::Media *newMedia) {
  if (!newMedia) return;

  // Aggiungi il nuovo media al database
  database_.addMedia(*newMedia);
  status_bar_->showMessage("Aggiunto media: " + QString::fromStdString(newMedia->getTitle()));
  changes_were_made_ = true;

  // Aggiorna i risultati della ricerca
  // media::Media *empty_filter = new media::Media("");
  applyFilterAdvanced(media::Media{});

  // Aggiorna la ricerca semplice
  // simple_search_widget_->acceptResults(database_.filterMedia(media::Media(last_simple_search_query_.toStdString())));
  simple_search_widget_->updateResults(database_.filterMedia(media::Media(last_simple_search_query_.toStdString())));

  // Pulisci lo stack per evitare ritorno alla AddMediaViewPage
  while (!navigation_stack_.empty()) navigation_stack_.pop();

  // Imposta esplicitamente che vogliamo tornare a simple_search_widget_
  navigation_stack_.push(simple_search_widget_);

  // Naviga alla pagina di dettaglio del nuovo media
  media_detail_page_->setMedia(newMedia);
  stacked_widget_->setCurrentWidget(media_detail_page_);
  add_media_view_page_->clearEditSection();  // Pulisce la sezione di modifica per il prossimo uso
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

  status_bar_->showMessage("Modificando media con titolo: " + QString::fromStdString(oldMedia->getTitle()));
  database_.removeMedia(*oldMedia);
  database_.addMedia(*newMedia);
  // todo memory leak
  changes_were_made_ = true;

  // Aggiorna la pagina dettaglio con il nuovo media
  media_detail_page_->setMedia(newMedia);

  // Aggiorna i risultati della ricerca (avanzata) per riflettere il cambiamento
  // media::Media *empty_filter = new media::Media("");
  applyFilterAdvanced(media::Media{});

  // Aggiorna ricerca semplice
  // simple_search_widget_->acceptResults(database_.filterMedia(media::Media(last_simple_search_query_.toStdString())));
  simple_search_widget_->updateResults(database_.filterMedia(media::Media(last_simple_search_query_.toStdString())));
}

bool MainWindow::savePopup() {
  if (changes_were_made_) {
    QMessageBox::StandardButton choice(
        QMessageBox::question(this, "Salvataggio", "Vuoi salvare?", QMessageBox::Yes | QMessageBox::No));

    if (choice == QMessageBox::No) changes_were_made_ = false;
  }
  return changes_were_made_;
}

// non c'`é una guardia contro database già aperto
// gestito da funzione chiamante
void MainWindow::accessDatabase(const QString &path) {
  database_.open(path);

  // Naviga alla schermata principale di ricerca avanzata (o altra)
  navigateTo(simple_search_widget_);
  simple_search_widget_->hidePreview();
}

void MainWindow::closeDatabase() {
  // bisogna aggiornare status line in base allo stato di chiusura del database
  savePopup();
  database_.close(changes_were_made_);
  status_bar_->showMessage("Chiuso database.");
  changes_were_made_ = false;

  // reset
  stacked_widget_->setCurrentWidget(db_selection_widget_);
  menuBar()->hide();
}

void MainWindow::saveDatabase() {
  database_.save();
  changes_were_made_ = false;
  status_bar_->showMessage("Salvato database.");
}

void MainWindow::applyFilterAdvanced(const media::Media &filter) {
  advanced_search_widget_->updateResults(database_.filterMedia(filter));
}

void MainWindow::simpleSearch(const media::Media &media) {
  last_simple_search_query_ = QString::fromStdString(media.getTitle());
  // simple_search_widget_->acceptResults(database_.filterMedia(media));
  simple_search_widget_->updateResults(database_.filterMedia(media));
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
  if (dynamic_cast<AbstractSearchWidget *>(next_page)) {
    current_search_widget_ = next_page;
    menuBar()->show();
  } else {
    menuBar()->hide();
  }
  // stacked_widget_->setCurrentWidget(next_page);
  stacked_widget_->slideInWgt(next_page);
}

}  // namespace gui
