#include "AudioBookEditWidget.h"

#include <QLabel>
#include <QComboBox> // aggiungi questa include

namespace gui {

AudioBookEditWidget::AudioBookEditWidget(QWidget* parent, bool min) : NovelEditWidget(parent, false, min) {
  auto* row_layout = new QHBoxLayout();
  // Label "Narratore"
  auto* narrator_label = new QLabel("Narratore:", this);
  narrator_label->setFixedWidth(70);
  narrator_input_ = new QLineEdit(this);
  narrator_input_->setFixedWidth(200);
  row_layout->addWidget(narrator_label);
  row_layout->addWidget(narrator_input_);

  row_layout->addSpacing(10); 

  // Label "Servizio Streaming"
  auto* streaming_label = new QLabel("Servizio Streaming:", this);
  streaming_label->setFixedWidth(130);

  // Usa QComboBox invece di QLineEdit
  streaming_service_ = new QComboBox(this);
  streaming_service_->addItems(kStreamingServices);
  streaming_service_->setFixedWidth(200);

  row_layout->addWidget(streaming_label);
  row_layout->addWidget(streaming_service_);

  row_layout->addStretch(); 

  main_layout_->addLayout(row_layout);

  addNotesSection(main_layout_);
}

void AudioBookEditWidget::setMedia(const media::Media* media) {
  NovelEditWidget::setMedia(media);

  const media::AudioBook* audiobook = dynamic_cast<const media::AudioBook*>(media);
  if (!audiobook) return;

  narrator_input_->setText(QString::fromStdString(audiobook->getNarrator()));

  // Imposta il valore selezionato nella combo box
  int idx = streaming_service_->findText(QString::fromStdString(audiobook->getStreamingService()));
  if (idx >= 0)
  streaming_service_->setCurrentIndex(idx);
  else
  streaming_service_->setCurrentIndex(0); // default su "Tutti"
}

media::Media* AudioBookEditWidget::getModifiedMedia(bool old) const {
  if (!old_media_ && old) return nullptr;

  return new media::AudioBook(title_input_->text().toStdString(), release_input_->value(),
                language_input_->text().toStdString(), favourite_checkbox_->isChecked(), getGenres(),
                img_path_input_->text().toStdString(), notes_input_->toPlainText().toStdString(),
                author_input_->text().toStdString(), publisher_input_->text().toStdString(),
                pages_input_->value(), series_input_->text().toStdString(),
                isbn_input_->text().toStdString(), narrator_input_->text().toStdString(),
                streaming_service_->currentText().toStdString());
}

void AudioBookEditWidget::clearInputFields() {
  NovelEditWidget::clearInputFields();
  narrator_input_->clear();
  streaming_service_->setCurrentIndex(0); // reset su "Tutti"
}

}  // namespace gui
