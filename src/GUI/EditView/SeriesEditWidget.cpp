#include "SeriesEditWidget.h"
#include <QLabel>
#include <QHBoxLayout>

namespace gui {

SeriesEditWidget::SeriesEditWidget(QWidget *parent) : MovieEditWidget(parent) {
  auto* episodes_layout = new QHBoxLayout();
  episodes_layout->addWidget(new QLabel("Episodi:", this));
  episodes_input_ = new QSpinBox(this);
  episodes_input_->setRange(0, 10000);
  episodes_layout->addWidget(episodes_input_);
  main_layout_->addLayout(episodes_layout);

  auto* seasons_layout = new QHBoxLayout();
  seasons_layout->addWidget(new QLabel("Stagioni:", this));
  seasons_input_ = new QSpinBox(this);
  seasons_input_->setRange(0, 1000);
  seasons_layout->addWidget(seasons_input_);
  main_layout_->addLayout(seasons_layout);

  auto* ended_layout = new QHBoxLayout();
  ended_layout->addWidget(new QLabel("Serie conclusa:", this));
  ended_checkbox_ = new QCheckBox(this);
  ended_layout->addWidget(ended_checkbox_);
  main_layout_->addLayout(ended_layout);
}



void SeriesEditWidget::setMedia(const media::Media* media) {
  MovieEditWidget::setMedia(media);

  const media::Series* series = dynamic_cast<const media::Series*>(media);
  if (!series) return;

  episodes_input_->setValue(series->getEpisodes());
  seasons_input_->setValue(series->getSeasons());
  ended_checkbox_->setChecked(series->hasEnded());
}

media::Media* SeriesEditWidget::getModifiedMedia() const {
  if (!old_media_) return nullptr;

  return new media::Series(
    title_input_->text().toStdString(),
    release_input_->value(),
    language_input_->text().toStdString(),
    favourite_checkbox_->isChecked(),
    getGenres(),
    img_path_input_->text().toStdString(),
    notes_input_->toPlainText().toStdString(),
    getCast(),
    length_input_->value(),
    universe_input_->text().toStdString(),
    episodes_input_->value(),
    seasons_input_->value(),
    ended_checkbox_->isChecked()
  );
}

}  // namespace gui
