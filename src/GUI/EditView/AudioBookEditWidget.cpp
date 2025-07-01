#include "AudioBookEditWidget.h"

#include <QLabel>

namespace gui {

AudioBookEditWidget::AudioBookEditWidget(QWidget* parent) : NovelEditWidget(parent, false) {
  auto* row_layout = new QHBoxLayout();

  // Label "Narratore"
  auto* narrator_label = new QLabel("Narratore:", this);
  narrator_label->setFixedWidth(70);
  narrator_input_ = new QLineEdit(this);
  narrator_input_->setFixedWidth(160);
  row_layout->addWidget(narrator_label);
  row_layout->addWidget(narrator_input_);

  row_layout->addSpacing(10);  // spazio tra i due blocchi

  // Label "Servizio Streaming"
  auto* streaming_label = new QLabel("Servizio Streaming:", this);
  streaming_label->setFixedWidth(130);
  streaming_service_input_ = new QLineEdit(this);
  streaming_service_input_->setFixedWidth(160);
  row_layout->addWidget(streaming_label);
  row_layout->addWidget(streaming_service_input_);

  row_layout->addStretch();  // allinea tutto a sinistra

  main_layout_->addLayout(row_layout);

  addNotesSection(main_layout_);
}

void AudioBookEditWidget::setMedia(const media::Media* media) {
  NovelEditWidget::setMedia(media);

  const media::AudioBook* audiobook = dynamic_cast<const media::AudioBook*>(media);
  if (!audiobook) return;

  narrator_input_->setText(QString::fromStdString(audiobook->getNarrator()));
  streaming_service_input_->setText(QString::fromStdString(audiobook->getStreamingService()));
}

media::Media* AudioBookEditWidget::getModifiedMedia(bool old) const {
  if (!old_media_ && old) return nullptr;

  return new media::AudioBook(title_input_->text().toStdString(), release_input_->value(),
                              language_input_->text().toStdString(), favourite_checkbox_->isChecked(), getGenres(),
                              img_path_input_->text().toStdString(), notes_input_->toPlainText().toStdString(),
                              author_input_->text().toStdString(), publisher_input_->text().toStdString(),
                              pages_input_->value(), series_input_->text().toStdString(),
                              isbn_input_->text().toStdString(), narrator_input_->text().toStdString(),
                              streaming_service_input_->text().toStdString());
}

void AudioBookEditWidget::clearInputFields() {
  NovelEditWidget::clearInputFields();
  narrator_input_->clear();
  streaming_service_input_->clear();
}

}  // namespace gui
