#include "AudioBookEditWidget.h"
#include <QLabel>

namespace gui {

AudioBookEditWidget::AudioBookEditWidget(QWidget *parent) : NovelEditWidget(parent) {
  auto* narrator_layout = new QHBoxLayout();
  narrator_layout->addWidget(new QLabel("Narratore:", this));
  narrator_input_ = new QLineEdit(this);
  narrator_layout->addWidget(narrator_input_);
  main_layout_->addLayout(narrator_layout);

  auto* streaming_layout = new QHBoxLayout();
  streaming_layout->addWidget(new QLabel("Servizio Streaming:", this));
  streaming_service_input_ = new QLineEdit(this);
  streaming_layout->addWidget(streaming_service_input_);
  main_layout_->addLayout(streaming_layout);
}



void AudioBookEditWidget::setMedia(const media::Media* media) {
  NovelEditWidget::setMedia(media);

  const media::AudioBook* audiobook = dynamic_cast<const media::AudioBook*>(media);
  if (!audiobook) return;

  narrator_input_->setText(QString::fromStdString(audiobook->getNarrator()));
  streaming_service_input_->setText(QString::fromStdString(audiobook->getStreamingService()));
}

media::Media* AudioBookEditWidget::getModifiedMedia() const {
  if (!old_media_) return nullptr;

  return new media::AudioBook(
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
    narrator_input_->text().toStdString(),
    streaming_service_input_->text().toStdString()
  );
}

}  // namespace gui
