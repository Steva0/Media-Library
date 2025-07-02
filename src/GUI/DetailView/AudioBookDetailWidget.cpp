#include "AudioBookDetailWidget.h"

namespace gui {

AudioBookDetailWidget::AudioBookDetailWidget(QWidget* parent) : NovelDetailWidget(parent, false) {
  narratorLabel_ = new QLabel("Narratore: ", this);
  leftLayout_->addWidget(narratorLabel_);

  streamingServiceLabel_ = new QLabel("Servizio Streaming: ", this);
  leftLayout_->addWidget(streamingServiceLabel_);
  
  leftLayout_->addWidget(notesLabel_);

  narratorLabel_->setWordWrap(true);
  streamingServiceLabel_->setWordWrap(true);
}

void AudioBookDetailWidget::setMedia(const media::Media* media) {
  NovelDetailWidget::setMedia(media);

  const media::AudioBook* audiobook = dynamic_cast<const media::AudioBook*>(media);
  if (!audiobook) {
    narratorLabel_->setText("Narratore: ");
    streamingServiceLabel_->setText("Servizio Streaming: ");
    return;
  }

  const std::string& narrator = audiobook->getNarrator();
  narratorLabel_->setText(QString("Narratore: %1").arg(narrator.empty() ? "" : QString::fromStdString(narrator)));

  const std::string& service = audiobook->getStreamingService();
  streamingServiceLabel_->setText(
      QString("Servizio Streaming: %1").arg(service.empty() ? "" : QString::fromStdString(service)));
}

void AudioBookDetailWidget::updateTextFontSize() {
  NovelDetailWidget::updateTextFontSize();  // Chiama la base per gestire le label comuni

  // Applica il font normale alle label aggiuntive
  narratorLabel_->setFont(normalLabelFont_);
  streamingServiceLabel_->setFont(normalLabelFont_);
}

}  // namespace gui
