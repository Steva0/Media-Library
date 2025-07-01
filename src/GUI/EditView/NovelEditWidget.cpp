#include "NovelEditWidget.h"

#include <QLabel>

namespace gui {

NovelEditWidget::NovelEditWidget(QWidget* parent, bool note) : MediaEditWidget(parent) {
  // Riga: Autore + Editore
  auto* first_row_layout = new QHBoxLayout();

  auto* author_label = new QLabel("Autore:", this);
  author_label->setFixedWidth(50);
  author_input_ = new QLineEdit(this);
  author_input_->setFixedWidth(170);
  first_row_layout->addWidget(author_label);
  first_row_layout->addWidget(author_input_);

  first_row_layout->addSpacing(10);  // spazio tra i due blocchi

  auto* publisher_label = new QLabel("Editore:", this);
  publisher_label->setFixedWidth(60);
  publisher_input_ = new QLineEdit(this);
  publisher_input_->setFixedWidth(170);
  first_row_layout->addWidget(publisher_label);
  first_row_layout->addWidget(publisher_input_);

  first_row_layout->addStretch();  // <-- forza l'allineamento a sinistra
  main_layout_->addLayout(first_row_layout);

  // Riga: Serie + Pagine + ISBN
  auto* second_row_layout = new QHBoxLayout();

  auto* series_label = new QLabel("Serie:", this);
  series_label->setFixedWidth(50);
  series_input_ = new QLineEdit(this);
  series_input_->setFixedWidth(150);
  second_row_layout->addWidget(series_label);
  second_row_layout->addWidget(series_input_);

  second_row_layout->addSpacing(10);

  pages_label = new QLabel("Pagine:", this);
  pages_label->setFixedWidth(60);
  pages_input_ = new QSpinBox(this);
  pages_input_->setRange(0, 10000);
  pages_input_->setFixedWidth(60);
  second_row_layout->addWidget(pages_label);
  second_row_layout->addWidget(pages_input_);

  second_row_layout->addSpacing(10);

  auto* isbn_label = new QLabel("ISBN:", this);
  isbn_label->setFixedWidth(40);
  isbn_input_ = new QLineEdit(this);
  isbn_input_->setFixedWidth(150);
  second_row_layout->addWidget(isbn_label);
  second_row_layout->addWidget(isbn_input_);

  second_row_layout->addStretch();  // <-- forza l'allineamento a sinistra
  main_layout_->addLayout(second_row_layout);

  if (note) {
    // Aggiungo la sezione note
    addNotesSection(main_layout_);
  }
}

void NovelEditWidget::setMedia(const media::Media* media) {
  MediaEditWidget::setMedia(media);

  const media::Novel* novel = dynamic_cast<const media::Novel*>(media);
  if (!novel) return;

  author_input_->setText(QString::fromStdString(novel->getAuthor()));
  publisher_input_->setText(QString::fromStdString(novel->getPublisher()));
  pages_input_->setValue(novel->getPages());
  series_input_->setText(QString::fromStdString(novel->getSeries()));
  isbn_input_->setText(QString::fromStdString(novel->getIsbn()));

  if (dynamic_cast<const media::AudioBook*>(media)) {
    pages_label->setText("Durata (min):");
    pages_label->setFixedWidth(90);
  }
}

media::Media* NovelEditWidget::getModifiedMedia(bool old) const {
  if (!old_media_ && old) return nullptr;

  return new media::Novel(title_input_->text().toStdString(), release_input_->value(),
                          language_input_->text().toStdString(), favourite_checkbox_->isChecked(), getGenres(),
                          img_path_input_->text().toStdString(), notes_input_->toPlainText().toStdString(),
                          author_input_->text().toStdString(), publisher_input_->text().toStdString(),
                          pages_input_->value(), series_input_->text().toStdString(),
                          isbn_input_->text().toStdString());
}

void NovelEditWidget::clearInputFields() {
  MediaEditWidget::clearInputFields();
  author_input_->clear();
  publisher_input_->clear();
  pages_input_->setValue(0);
  series_input_->clear();
  isbn_input_->clear();
}

}  // namespace gui
