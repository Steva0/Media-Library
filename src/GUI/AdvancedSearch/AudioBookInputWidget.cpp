#include "AudioBookInputWidget.h"
#include "../../Media/AudioBook.h"
#include <QGridLayout>
#include <QLabel>

namespace gui {
namespace advanced_search {
const QStringList AudioBookInputWidget::kStreamingServices{
    "Any", "Audible", "Audiobooks.com", "B&N Audiobooks", "Libro.fm", "Everand", "Spotify", "Libby", "Hoopla", "Chirp"};

AudioBookInputWidget::AudioBookInputWidget(QWidget *parent) : NovelInputWidget(parent) {
  narrator_ = new QLineEdit(this);
  streaming_service_ = new QComboBox(this);
  streaming_service_->addItems(kStreamingServices);

  novel_layout_->addWidget(new QLabel("Voice:", this), novel_layout_->rowCount(), 0);
  novel_layout_->addWidget(narrator_, novel_layout_->rowCount() - 1, 1);

  novel_layout_->addWidget(new QLabel("Streaming:", this), novel_layout_->rowCount() - 1, 2);
  novel_layout_->addWidget(streaming_service_, novel_layout_->rowCount() - 1, 3);
}
media::AudioBook *AudioBookInputWidget::getFilter() const {
  auto *novel = NovelInputWidget::getFilter();
  auto *audio_book = new media::AudioBook(*novel);
  delete novel;

  audio_book->setNarrator(narrator_->text().toStdString());
  if (streaming_service_->currentText() != "Any")
    audio_book->setStreamingService(streaming_service_->currentText().toStdString());
  return audio_book;
}
}  // namespace advanced_search
}  // namespace gui
