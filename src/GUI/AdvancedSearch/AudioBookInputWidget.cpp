#include "AudioBookInputWidget.h"

#include <QGridLayout>
#include <QLabel>
#include "InputWidget.h"

#include "../../Media/AudioBook.h"

namespace gui {
namespace advanced_search {

AudioBookInputWidget::AudioBookInputWidget(QWidget *parent) : NovelInputWidget(parent) {
  narrator_ = new QLineEdit(this);
  streaming_service_ = new QComboBox(this);
  streaming_service_->addItems(kStreamingServices);

  novel_layout_->addWidget(new QLabel("Narratore:", this), novel_layout_->rowCount(), 0);
  novel_layout_->addWidget(narrator_, novel_layout_->rowCount() - 1, 1);

  novel_layout_->addWidget(new QLabel("Streaming:", this), novel_layout_->rowCount() - 1, 2);
  novel_layout_->addWidget(streaming_service_, novel_layout_->rowCount() - 1, 3);
}
void AudioBookInputWidget::makeFilterFor(InputWidget &other) const {
  other.makeFilterFrom(*this);
}
void AudioBookInputWidget::setFromMedia(const media::Media &media) {
  NovelInputWidget::setFromMedia(media);
  if (const auto *audiobook = dynamic_cast<const media::AudioBook *>(&media)) {
    narrator_->setText(QString::fromStdString(audiobook->getNarrator()));
    streaming_service_->setEditText(QString::fromStdString(audiobook->getStreamingService()));
  }
}
std::string AudioBookInputWidget::getNarrator() const { return narrator_->text().toStdString(); }
std::string AudioBookInputWidget::getStreamingService() const {
  QString service = streaming_service_->currentText();
  return (service == "Tutti") ? "" : service.toStdString();
}
}  // namespace advanced_search
}  // namespace gui
