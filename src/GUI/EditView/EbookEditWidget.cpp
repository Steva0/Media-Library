#include "EbookEditWidget.h"
#include <QLabel>

namespace gui {

EbookEditWidget::EbookEditWidget(QWidget *parent) : NovelEditWidget(parent) {
  auto* file_size_layout = new QHBoxLayout();
  file_size_layout->addWidget(new QLabel("Dimensione file (bytes):", this));
  file_size_input_ = new QSpinBox(this);
  file_size_input_->setRange(0, 1'000'000'000);
  file_size_layout->addWidget(file_size_input_);
  main_layout_->addLayout(file_size_layout);

  auto* drm_layout = new QHBoxLayout();
  drm_layout->addWidget(new QLabel("DRM:", this));
  drm_checkbox_ = new QCheckBox(this);
  drm_layout->addWidget(drm_checkbox_);
  main_layout_->addLayout(drm_layout);
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
