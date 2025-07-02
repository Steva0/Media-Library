#include "AddMediaViewPage.h"

#include <iostream>

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QKeyEvent>

namespace gui {

AddMediaViewPage::AddMediaViewPage(QWidget* parent) : QWidget(parent) {
  setupUi();
}

void AddMediaViewPage::setupUi() {
  auto* main_layout = new QVBoxLayout(this);

  // Top bar
  auto* top_bar_layout = new QHBoxLayout();
  auto* back_button = new QPushButton("Indietro", this);
  back_button->setFixedSize(80, 30);
  connect(back_button, &QPushButton::clicked, this, &AddMediaViewPage::onBack);
  top_bar_layout->addWidget(back_button);
  top_bar_layout->addStretch();
  main_layout->addLayout(top_bar_layout);

  // --- Usa DUE widget pulsanti separati ---
  auto* buttons_widget_selector = createButtonsWidget(this);
  auto* buttons_widget_full = createButtonsWidget(this);

  // --- Sezione edit ---
  edit_section_ = new QWidget(this);
  auto* edit_section_layout = new QVBoxLayout(edit_section_);
  edit_section_layout->setContentsMargins(0, 0, 0, 0);

  stacked_layout_ = new QStackedLayout();
  novel_edit_widget_ = new NovelEditWidget(this);
  ebook_edit_widget_ = new EbookEditWidget(this);
  audiobook_edit_widget_ = new AudioBookEditWidget(this, true);
  movie_edit_widget_ = new MovieEditWidget(this);
  series_edit_widget_ = new SeriesEditWidget(this);
  album_edit_widget_ = new AlbumEditWidget(this);

  stacked_layout_->addWidget(novel_edit_widget_);
  stacked_layout_->addWidget(ebook_edit_widget_);
  stacked_layout_->addWidget(audiobook_edit_widget_);
  stacked_layout_->addWidget(movie_edit_widget_);
  stacked_layout_->addWidget(series_edit_widget_);
  stacked_layout_->addWidget(album_edit_widget_);

  stacked_layout_->setCurrentIndex(0);
  edit_section_layout->addLayout(stacked_layout_);

  // Bottom bar con bottone conferma
  auto* bottom_layout = new QHBoxLayout();
  auto* confirm_button = new QPushButton("Aggiungi", this);
  connect(confirm_button, &QPushButton::clicked, this, &AddMediaViewPage::onConfirm);
  bottom_layout->addStretch();
  bottom_layout->addWidget(confirm_button);
  edit_section_layout->addLayout(bottom_layout);

  // --- Due pagine nello stacked layout centrale ---

  // Pagina 0: solo pulsanti (selector)
  auto* selector_page = new QWidget(this);
  auto* selector_layout = new QVBoxLayout(selector_page);
  selector_layout->setContentsMargins(0,0,0,0);
  selector_layout->addWidget(buttons_widget_selector);
  selector_layout->addStretch();

  // Pagina 1: pulsanti + sezione edit
  auto* full_edit_page = new QWidget(this);
  auto* full_layout = new QVBoxLayout(full_edit_page);
  full_layout->setContentsMargins(0,0,0,0);
  full_layout->addWidget(buttons_widget_full);
  full_layout->addWidget(edit_section_);

  // Stacked layout centrale che mostra selector_page o full_edit_page
  central_layout_ = new QStackedLayout();
  central_layout_->addWidget(selector_page);   // index 0 - iniziale
  central_layout_->addWidget(full_edit_page);  // index 1 - dopo selezione

  main_layout->addLayout(central_layout_);

  // Nascondiamo la sezione edit di default (anche se è in full_edit_page)
  edit_section_->setVisible(false);
  // Impostiamo la pagina iniziale a selector_page con solo i pulsanti in alto
  central_layout_->setCurrentIndex(0);
  clearEditSection();
}

void AddMediaViewPage::selectMediaType(int index) {
  // Cambia pagina edit widget interno
  stacked_layout_->setCurrentIndex(index);

  // Mostra la sezione edit (solo se nascosta)
  if (!edit_section_->isVisible()) {
    edit_section_->setVisible(true);
  }

  // Cambia pagina centrale da selector_page (0) a full_edit_page (1)
  if (central_layout_->currentIndex() != 1) {
    central_layout_->setCurrentIndex(1);
  }
}

void AddMediaViewPage::onConfirm() {
  auto* current_widget = getWidgetAtIndex(stacked_layout_->currentIndex());
  if (!current_widget) return;

  media::Media* media = current_widget->getModifiedMedia(false);
  if (media && !media->getTitle().empty() && media->getTitle() != "") {
    emit mediaAdded(media);
    clearEditSection();
  }
}

MediaEditWidget* AddMediaViewPage::getWidgetAtIndex(int index) const {
  switch (index) {
    case 0: return novel_edit_widget_;
    case 1: return ebook_edit_widget_;
    case 2: return audiobook_edit_widget_;
    case 3: return movie_edit_widget_;
    case 4: return series_edit_widget_;
    case 5: return album_edit_widget_;
    default: return nullptr;
  }
}

void AddMediaViewPage::onBack() {
  // Torna alla pagina con solo i pulsanti
  central_layout_->setCurrentIndex(0);
  
  emit backRequested();
  clearEditSection();
}

void AddMediaViewPage::clearEditSection(){
  novel_edit_widget_->clearInputFields();
  ebook_edit_widget_->clearInputFields();
  audiobook_edit_widget_->clearInputFields();
  movie_edit_widget_->clearInputFields();
  series_edit_widget_->clearInputFields();
  album_edit_widget_->clearInputFields();
  central_layout_->setCurrentIndex(0);
}


void AddMediaViewPage::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Escape) {
    onBack();
    event->accept();
  } else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
    onConfirm();
    event->accept();
  } else {
    QWidget::keyPressEvent(event);
  }
}

QWidget* AddMediaViewPage::createButtonsWidget(QWidget* parent) {
  auto* container = new QWidget(parent);

  // Layout verticale per tutta la sezione
  auto* vertical_layout = new QVBoxLayout(container);
  vertical_layout->setContentsMargins(0, 0, 0, 0);
  vertical_layout->setSpacing(10);

  // Container orizzontale con pulsanti a sinistra e stretch a destra
  auto* row_container = new QWidget(container);
  auto* row_layout = new QHBoxLayout(row_container);
  row_layout->setContentsMargins(0, 0, 0, 0);

  // Colonna dei pulsanti (e label sopra)
  auto* column_widget = new QWidget(row_container);
  auto* column_layout = new QVBoxLayout(column_widget);
  column_layout->setContentsMargins(0, 0, 0, 0);
  column_layout->setSpacing(5);

  // Label centrata rispetto ai pulsanti
  auto* label = new QLabel("Selezionare tipologia di Media", column_widget);
  label->setAlignment(Qt::AlignHCenter);
  QFont font = label->font();
  font.setPointSize(11);
  font.setBold(true);
  label->setFont(font);
  column_layout->addWidget(label);

  // Layout dei pulsanti
  auto* buttons_container = new QWidget(column_widget);
  auto* buttons_layout = new QHBoxLayout(buttons_container);
  buttons_layout->setContentsMargins(0, 0, 0, 0);
  buttons_layout->setSpacing(5);

  const QStringList labels = {
    "Libro", "EBook", "Audiobook", "Film", "Serie", "Album"
  };
  for (int i = 0; i < labels.size(); ++i) {
    auto* button = new QPushButton(labels[i], buttons_container);
    connect(button, &QPushButton::clicked, this, [this, i]() { selectMediaType(i); });
    buttons_layout->addWidget(button);
  }

  column_layout->addWidget(buttons_container);

  // Aggiungi la colonna al layout orizzontale, poi lo stretch
  row_layout->addWidget(column_widget, 2);
  row_layout->addStretch(1);

  // Infine aggiungi tutto al layout verticale
  vertical_layout->addWidget(row_container);

  return container;
}
}  // namespace gui
