#include "EbookEditWidget.h"
#include <QLabel>

namespace gui {

EbookEditWidget::EbookEditWidget(QWidget *parent) : NovelEditWidget(parent) {
  auto* row_layout = new QHBoxLayout();

  // Label "Dimensione file"
  auto* size_label = new QLabel("Dimensione file (bytes):  ", this);
  size_label->setFixedWidth(170);
  row_layout->addWidget(size_label);

  // Campo input: massimo 7 cifre
  file_size_input_ = new QSpinBox(this);
  file_size_input_->setRange(0, 9'999'999);  // max 7 cifre
  file_size_input_->setFixedWidth(100);
  row_layout->addWidget(file_size_input_);

  row_layout->addSpacing(15);  // spazio tra i due blocchi

  // Label "DRM"
  auto* drm_label = new QLabel("DRM:", this);
  drm_label->setFixedWidth(40);
  row_layout->addWidget(drm_label);

  // Checkbox DRM
  drm_checkbox_ = new QCheckBox(this);
  row_layout->addWidget(drm_checkbox_);

  row_layout->addStretch();  // allinea tutto a sinistra
  main_layout_->addLayout(row_layout);
}


void EbookEditWidget::setMedia(const media::Media* media) {
  NovelEditWidget::setMedia(media);

  const media::Ebook* Ebook = dynamic_cast<const media::Ebook*>(media);
  if (!Ebook) return;

  file_size_input_->setValue(Ebook->getFileSizeBytes());
  drm_checkbox_->setChecked(Ebook->hasDrm());
}

media::Media* EbookEditWidget::getModifiedMedia() const {
  if (!old_media_) return nullptr;

  return new media::Ebook(
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
    isbn_input_->text().toStdString(),
    file_size_input_->value(),
    drm_checkbox_->isChecked()
  );
}

}  // namespace gui
