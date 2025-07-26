#include "MediaEditWidget.h"

#include <QCheckBox>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include <QScrollArea>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <algorithm>

namespace gui {

MediaEditWidget::MediaEditWidget(QWidget* parent) : IMediaEditWidget(parent) {
  // Layout principale orizzontale
  auto* split_layout = new QHBoxLayout(this);

  // Widget principale con layout verticale (form)
  auto* main_form_widget = new QWidget(this);
  main_layout_ = new QVBoxLayout(main_form_widget);
  main_layout_->setAlignment(Qt::AlignTop);
  main_form_widget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

  // Aggiungo form a sinistra (2/3)
  split_layout->addWidget(main_form_widget, 2, Qt::AlignTop);

  // Label copertina a destra (1/3)
  cover_label_ = new QLabel(this);
  cover_label_->setAlignment(Qt::AlignCenter);
  split_layout->addWidget(cover_label_, 1);

  // Titolo
  auto* title_layout = new QHBoxLayout();
  auto* title_label = new QLabel(tr("Titolo:"), this);
  title_label->setFixedWidth(50);
  title_input_ = new QLineEdit(this);
  title_input_->setFixedWidth(250);
  title_layout->addWidget(title_label);
  title_layout->addWidget(title_input_);
  title_layout->addStretch();
  main_layout_->addLayout(title_layout);

  // Riga con Anno di uscita, Lingua e Preferito
  auto* row_layout = new QHBoxLayout();

  // Anno di uscita
  auto* release_label = new QLabel(tr("Anno di uscita:"), this);
  release_input_ = new QSpinBox(this);
  release_input_->setRange(0, 4000);
  row_layout->addWidget(release_label);
  row_layout->addWidget(release_input_);

  // Lingua
  auto* language_label = new QLabel(tr("Lingua:"), this);
  language_input_ = new QLineEdit(this);
  language_input_->setFixedWidth(150);
  row_layout->addSpacing(10);  // Spazio tra i campi
  row_layout->addWidget(language_label);
  row_layout->addWidget(language_input_);

  // Preferito
  auto* favourite_label = new QLabel(tr("Preferito:"), this);
  favourite_checkbox_ = new QCheckBox(this);
  row_layout->addSpacing(10);  // Spazio tra i campi
  row_layout->addWidget(favourite_label);
  row_layout->addWidget(favourite_checkbox_);
  row_layout->addStretch();

  main_layout_->addLayout(row_layout);

  // Percorso immagine (label + pulsante + path sotto)
  img_select_button_ = new QPushButton(tr("Seleziona immagine..."), this);
  img_path_input_ = new QLabel(tr("(nessuna immagine selezionata)"), this);
  img_path_input_->setStyleSheet("font-style: italic; color: gray;");

  auto* img_layout = new QHBoxLayout();
  img_label_ = new QLabel(tr("Percorso immagine:"), this);
  img_layout->addWidget(img_label_);
  img_layout->addWidget(img_path_input_);
  img_layout->addStretch();
  main_layout_->addLayout(img_layout);
  main_layout_->addWidget(img_select_button_);

  // Imposta immagine di default (matita)
  QPixmap default_pixmap(":/icons/pencil.png");  // Assicurati che il path sia corretto
  if (!default_pixmap.isNull()) {
      cover_label_->setPixmap(default_pixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
  } else {
      cover_label_->setText("Errore caricamento immagine di default");
  }

  connect(img_select_button_, &QPushButton::clicked, this, &MediaEditWidget::selectImageFile);

  // Layout orizzontale per l'intera sezione "Generi"
  auto* genres_row_layout = new QHBoxLayout();

  // Label "Generi" (in alto a sinistra)
  auto* genres_label = new QLabel(tr("Generi:"), this);
  genres_label->setAlignment(Qt::AlignTop);
  genres_row_layout->addWidget(genres_label);

  // Layout verticale per input + lista a destra
  auto* genres_right_layout = new QVBoxLayout();

  // Campo input e bottone "+"
  genre_input_ = new QLineEdit(this);
  add_genre_button_ = new QPushButton(tr("+"), this);
  add_genre_button_->setFixedWidth(30);

  auto* add_genre_layout = new QHBoxLayout();
  add_genre_layout->addWidget(genre_input_);
  add_genre_layout->addWidget(add_genre_button_);
  genres_right_layout->addLayout(add_genre_layout);

  // Lista dei generi (scrollable)
  genres_layout_ = new QGridLayout();
  genres_layout_->setSpacing(5);
  genres_layout_->setContentsMargins(0, 0, 0, 0);

  auto* genres_container = new QWidget(this);
  genres_container->setLayout(genres_layout_);

  auto* genres_scroll = new QScrollArea(this);
  genres_scroll->setWidget(genres_container);
  genres_scroll->setWidgetResizable(true);
  genres_scroll->setFixedHeight(100);

  genres_right_layout->addWidget(genres_scroll);

  // Aggiungo il layout destro a fianco della label
  genres_row_layout->addLayout(genres_right_layout);

  // Aggiungo il layout dei generi al layout principale
  main_layout_->addLayout(genres_row_layout);

  connect(add_genre_button_, &QPushButton::clicked, this, &MediaEditWidget::addGenre);

  notes_label_ = new QLabel();
  notes_input_ = new QTextEdit();
  
  old_media_ = nullptr;
  img_path_.clear();
}

void MediaEditWidget::selectImageFile() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Seleziona immagine"), QString(),
                                                  tr("Immagini (*.png *.jpg *.jpeg *.bmp *.gif)"));

  if (!fileName.isEmpty()) {
    QPixmap test_pixmap(fileName);
    if (!test_pixmap.isNull()) {
      img_path_ = fileName;
      img_path_input_->setText(img_path_);
      img_path_input_->setStyleSheet("");
      img_label_->setText("Percorso immagine:");
      cover_pixmap_ = test_pixmap;
    } else {
      // Immagine non caricabile
      img_path_.clear();
      img_path_input_->setText("(nessuna immagine selezionata)");
      img_path_input_->setStyleSheet("font-style: italic; color: gray;");
      img_label_->setText("Percorso immagine:");
      cover_pixmap_ = QPixmap(":/assets/matita.jpg");  // fallback
    }

    updateCoverPixmap();
  }
}


void MediaEditWidget::updateCoverPixmap() {
  if (cover_pixmap_.isNull()) {
    cover_label_->clear();
    return;
  }

  int targetWidth = width() / 3;
  int targetHeight = cover_pixmap_.height() * targetWidth / cover_pixmap_.width();

  cover_label_->setPixmap(
      cover_pixmap_.scaled(targetWidth, targetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MediaEditWidget::resizeEvent(QResizeEvent* event) {
  IMediaEditWidget::resizeEvent(event);
  updateCoverPixmap();
}

void MediaEditWidget::setMedia(const media::Media* media) {
  if (!media) {
    // Media non valido -> resetto campi e metto immagine di default
    title_input_->clear();
    release_input_->setValue(0);
    language_input_->clear();
    favourite_checkbox_->setChecked(false);
    notes_input_->clear();
    clearGenres();

    img_path_.clear();
    img_path_input_->clear();  // Nessun testo indicato
    img_path_input_->setStyleSheet("");
    img_label_->setText("Percorso immagine:");

    cover_pixmap_ = QPixmap(":/assets/matita.jpg");  // immagine di default
    updateCoverPixmap();

    old_media_ = nullptr;
    return;
  }

  // Se media valido
  old_media_ = media;

  title_input_->setText(QString::fromStdString(media->getTitle()));
  release_input_->setValue(media->getRelease());
  language_input_->setText(QString::fromStdString(media->getLanguage()));
  favourite_checkbox_->setChecked(media->isFavourite());

  const QString img_path = QString::fromStdString(media->getImgPath());
  QPixmap test_pixmap(img_path);

  if (!img_path.isEmpty() && !test_pixmap.isNull()) {
    img_path_ = img_path;
    img_path_input_->setText(img_path_);
    img_path_input_->setStyleSheet("");
    cover_pixmap_ = test_pixmap;
    img_label_->setText("Percorso immagine:");
  } else {
    img_path_.clear();  // Consideriamo il path non valido
    img_path_input_->clear();  // Nessuna dicitura "nessuna immagine selezionata"
    img_path_input_->setStyleSheet("");
    cover_pixmap_ = QPixmap(":/assets/matita.jpg");
    img_label_->setText("Percorso immagine: (nessuna immagine selezionata)");
  }
 
  updateCoverPixmap();

  notes_input_->setText(QString::fromStdString(media->getNotes()));

  clearGenres();
  setGenres(media->getGenres());
}

void MediaEditWidget::setGenres(const std::vector<std::string>& genres) {
  int row = 0;
  for (const auto& genre : genres) {
    auto* genre_line = new QLineEdit(QString::fromStdString(genre), this);
    genre_line->setEnabled(false);
    genres_layout_->addWidget(genre_line, row, 0);
    genres_.push_back(genre_line);

    auto* remove_button = new QPushButton("-", this);
    remove_button->setFixedWidth(30);
    genres_layout_->addWidget(remove_button, row, 1);

    connect(remove_button, &QPushButton::clicked, this,
            [this, genre_line, remove_button]() { removeGenre(genre_line, remove_button); });

    row++;
  }
}

void MediaEditWidget::addGenre() {
  QString text = genre_input_->text().trimmed();
  if (text.isEmpty()) return;

  auto it = std::find_if(genres_.begin(), genres_.end(), [&](QLineEdit* le) { return le->text() == text; });
  if (it != genres_.end()) {
    genre_input_->clear();
    return;
  }

  int row = genres_layout_->rowCount();

  auto* new_genre = new QLineEdit(text, this);
  new_genre->setEnabled(false);
  genres_layout_->addWidget(new_genre, row, 0);
  genres_.push_back(new_genre);

  auto* remove_button = new QPushButton("-", this);
  remove_button->setFixedWidth(30);
  genres_layout_->addWidget(remove_button, row, 1);

  connect(remove_button, &QPushButton::clicked, this,
          [this, new_genre, remove_button]() { removeGenre(new_genre, remove_button); });

  genre_input_->clear();
}

void MediaEditWidget::removeGenre(QLineEdit* genre, QPushButton* button) {
  auto it = std::find(genres_.begin(), genres_.end(), genre);
  if (it == genres_.end()) return;

  genres_layout_->removeWidget(genre);
  genre->deleteLater();
  genres_.erase(it);

  genres_layout_->removeWidget(button);
  button->deleteLater();
}

std::vector<std::string> MediaEditWidget::getGenres() const {
  std::vector<std::string> result;
  for (auto* genre_line : genres_) {
    result.push_back(genre_line->text().toStdString());
  }
  return result;
}

media::Media* MediaEditWidget::getModifiedMedia(bool old) const {
  if (!old_media_ && old) return nullptr;

  return new media::Media(title_input_->text().toStdString(), release_input_->value(),
                          language_input_->text().toStdString(), favourite_checkbox_->isChecked(), getGenres(),
                          img_path_.toStdString(), notes_input_->toPlainText().toStdString());
}

void MediaEditWidget::addNotesSection(QVBoxLayout* layout) {
  QHBoxLayout* notes_layout = new QHBoxLayout;
  notes_label_ = new QLabel(tr("Note:"), this);
  notes_input_ = new QTextEdit(this);
  const int line_height = QFontMetrics(notes_input_->font()).lineSpacing();
  notes_input_->setFixedHeight(line_height * 6 + 12);
 
  notes_layout->addWidget(notes_label_, 0, Qt::AlignTop);
  notes_layout->addWidget(notes_input_, 1); 
  layout->addLayout(notes_layout);
}

void MediaEditWidget::clearInputFields() {
  title_input_->clear();
  release_input_->setValue(0);
  language_input_->clear();
  favourite_checkbox_->setChecked(false);
  notes_input_->clear();
  
  clearGenres();
  
  img_path_.clear();
  img_label_->setText("Percorso immagine: (nessuna immagine selezionata)");
  img_path_input_->setStyleSheet("font-style: italic; color: gray;");
  
  cover_pixmap_ = QPixmap(":/assets/matita.jpg");  // immagine di default
  updateCoverPixmap();
}

void MediaEditWidget::clearGenres() {
  // Rimuove tutti i widget nel layout dei generi
  QLayoutItem* child;
  while ((child = genres_layout_->takeAt(0)) != nullptr) {
    if (QWidget* widget = child->widget()) {
      genres_layout_->removeWidget(widget);
      widget->deleteLater();
    }
    delete child;
  }
  genres_.clear();
}

}  // namespace gui
