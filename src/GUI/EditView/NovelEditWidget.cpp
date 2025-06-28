#include "NovelEditWidget.h"
#include <QLabel>

namespace gui {

NovelEditWidget::NovelEditWidget(QWidget *parent) : MediaEditWidget(parent) {
  auto addRow = [this](const QString& label_text, QWidget* widget) {
    auto* layout = new QHBoxLayout();
    layout->addWidget(new QLabel(label_text, this));
    layout->addWidget(widget);
    main_layout_->addLayout(layout);
  };

  author_input_ = new QLineEdit(this);
  addRow("Autore:", author_input_);

  publisher_input_ = new QLineEdit(this);
  addRow("Editore:", publisher_input_);

  pages_input_ = new QSpinBox(this);
  pages_input_->setRange(1, 10000);
  addRow("Pagine:", pages_input_);

  series_input_ = new QLineEdit(this);
  addRow("Serie:", series_input_);

  isbn_input_ = new QLineEdit(this);
  addRow("ISBN:", isbn_input_);
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
}

media::Media* NovelEditWidget::getModifiedMedia() const {
  if (!old_media_) return nullptr;

  return new media::Novel(
    title_input_->text().toStdString(),
    release_input_->value(),
    language_input_->text().toStdString(),
    favourite_checkbox_->isChecked(),
    getGenres(),
    img_path_input_->text().toStdString(),
    notes_input_->toPlainText().toStdString(),
    author_input_->text().toStdString(),
    publisher_input_->text().toStdString(),
    pages_input_->value(),
    series_input_->text().toStdString(),
    isbn_input_->text().toStdString()
  );
}

}  // namespace gui
