#include "AudioBookDetailWidget.h"

namespace gui {

AudioBookDetailWidget::AudioBookDetailWidget(QWidget* parent) : NovelDetailWidget(parent, false) {
  narratorLabel_ = new QLabel("Narrator: ", this);
  leftLayout_->addWidget(narratorLabel_);

  streamingServiceLabel_ = new QLabel("Streaming Service: ", this);
  leftLayout_->addWidget(streamingServiceLabel_);
  
  leftLayout_->addWidget(notesLabel_);
}

void AudioBookDetailWidget::setMedia(const media::Media* media) {
  NovelDetailWidget::setMedia(media);

  const media::AudioBook* audiobook = dynamic_cast<const media::AudioBook*>(media);
  if (!audiobook) {
    narratorLabel_->setText("Narrator: ");
    streamingServiceLabel_->setText("Streaming Service: ");
    return;
  }

  const std::string& narrator = audiobook->getNarrator();
  narratorLabel_->setText(QString("Narrator: %1").arg(narrator.empty() ? "" : QString::fromStdString(narrator)));

  const std::string& service = audiobook->getStreamingService();
  streamingServiceLabel_->setText(
      QString("Streaming Service: %1").arg(service.empty() ? "" : QString::fromStdString(service)));
}

void AudioBookDetailWidget::updateTextFontSize() {
  NovelDetailWidget::updateTextFontSize();  // Chiama la base per gestire le label comuni

  // Applica il font normale alle label aggiuntive
  narratorLabel_->setFont(normalLabelFont_);
  streamingServiceLabel_->setFont(normalLabelFont_);
}

}  // namespace gui
