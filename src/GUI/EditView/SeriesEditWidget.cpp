#include "SeriesEditWidget.h"

#include <QHBoxLayout>
#include <QLabel>

namespace gui {

SeriesEditWidget::SeriesEditWidget(QWidget* parent) : MovieEditWidget(parent, false) {
  // Layout orizzontale principale per i 3 campi
  auto* main_row_layout = new QHBoxLayout();
  main_row_layout->setAlignment(Qt::AlignLeft);  // Allinea a sinistra
  main_row_layout->setSpacing(10);               // Spazio ridotto tra i blocchi

  // Episodi
  auto* episodes_layout = new QHBoxLayout();
  episodes_layout->setContentsMargins(0, 0, 0, 0);
  episodes_layout->addWidget(new QLabel("Episodi:", this));
  episodes_input_ = new QSpinBox(this);
  episodes_input_->setRange(0, 10000);
  episodes_layout->addWidget(episodes_input_);
  auto* episodes_container = new QWidget(this);
  episodes_container->setLayout(episodes_layout);
  main_row_layout->addWidget(episodes_container);

  // Stagioni
  auto* seasons_layout = new QHBoxLayout();
  seasons_layout->setContentsMargins(0, 0, 0, 0);
  seasons_layout->addWidget(new QLabel("Stagioni:", this));
  seasons_input_ = new QSpinBox(this);
  seasons_input_->setRange(0, 1000);
  seasons_layout->addWidget(seasons_input_);
  auto* seasons_container = new QWidget(this);
  seasons_container->setLayout(seasons_layout);
  main_row_layout->addWidget(seasons_container);

  // Serie conclusa
  auto* ended_layout = new QHBoxLayout();
  ended_layout->setContentsMargins(0, 0, 0, 0);
  ended_layout->addWidget(new QLabel("Serie conclusa:", this));
  ended_checkbox_ = new QCheckBox(this);
  ended_layout->addWidget(ended_checkbox_);
  auto* ended_container = new QWidget(this);
  ended_container->setLayout(ended_layout);
  main_row_layout->addWidget(ended_container);

  // Aggiungo al layout verticale
  main_layout_->addLayout(main_row_layout);

  addNotesSection(main_layout_);
}

void SeriesEditWidget::setMedia(const media::Media* media) {
  MovieEditWidget::setMedia(media);

  const media::Series* series = dynamic_cast<const media::Series*>(media);
  if (!series) return;

  episodes_input_->setValue(series->getEpisodes());
  seasons_input_->setValue(series->getSeasons());
  ended_checkbox_->setChecked(series->hasEnded());
}

media::Media* SeriesEditWidget::getModifiedMedia(bool old) const {
  if (!old_media_ && old) return nullptr;

  return new media::Series(title_input_->text().toStdString(), release_input_->value(),
                           language_input_->text().toStdString(), favourite_checkbox_->isChecked(), getGenres(),
                           img_path_input_->text().toStdString(), notes_input_->toPlainText().toStdString(), getCast(),
                           length_input_->value(), universe_input_->text().toStdString(), episodes_input_->value(),
                           seasons_input_->value(), ended_checkbox_->isChecked());
}

}  // namespace gui
