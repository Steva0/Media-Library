#include "SeriesDetailWidget.h"
#include <QString>

namespace gui {

SeriesDetailWidget::SeriesDetailWidget(QWidget* parent) : MovieDetailWidget(parent) {
  episodesLabel_ = new QLabel("Episodes: ", this);
  seasonsLabel_ = new QLabel("Seasons: ", this);
  endedLabel_ = new QLabel("Ended: ", this);

  // Usa il leftLayout_ ereditato da MovieDetailWidget (che a sua volta da MediaDetailWidget)
  leftLayout_->addWidget(episodesLabel_);
  leftLayout_->addWidget(seasonsLabel_);
  leftLayout_->addWidget(endedLabel_);
}

void SeriesDetailWidget::setMedia(const media::Media* media) {
  MovieDetailWidget::setMedia(media);

  const media::Series* series = dynamic_cast<const media::Series*>(media);
  if (!series) {
    episodesLabel_->setText("Episodes: ");
    seasonsLabel_->setText("Seasons: ");
    endedLabel_->setText("Ended: ");
    return;
  }

  int episodes = series->getEpisodes();
  episodesLabel_->setText((episodes > 0) ? QString("Episodes: %1").arg(episodes) : "Episodes: ");

  int seasons = series->getSeasons();
  seasonsLabel_->setText((seasons > 0) ? QString("Seasons: %1").arg(seasons) : "Seasons: ");

  // Per ended mettiamo "Yes", "No" o campo vuoto se valore non definito
  endedLabel_->setText(series->hasEnded() ? "Ended: Yes" : "Ended: No");
}


}  // namespace gui
