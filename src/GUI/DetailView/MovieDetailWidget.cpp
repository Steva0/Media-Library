#include "MovieDetailWidget.h"
#include <QString>

namespace gui {

MovieDetailWidget::MovieDetailWidget(QWidget* parent) : MediaDetailWidget(parent) {
  lengthLabel_ = new QLabel("Length (min): ", this);
  universeLabel_ = new QLabel("Universe: ", this);
  castLabel_ = new QLabel("Cast: ", this);

  // Usa il leftLayout_ ereditato da MediaDetailWidget
  leftLayout_->addWidget(lengthLabel_);
  leftLayout_->addWidget(universeLabel_);
  leftLayout_->addWidget(castLabel_);
}

void MovieDetailWidget::setMedia(const media::Media* media) {
  MediaDetailWidget::setMedia(media);

  const media::Movie* movie = dynamic_cast<const media::Movie*>(media);
  if (!movie) {
    lengthLabel_->setText("Length (min): ");
    universeLabel_->setText("Universe: ");
    castLabel_->setText("Cast: ");
    return;
  }

  // Controllo length, 0 o negativo lo considero "vuoto"
  if (movie->getLength() > 0) {
    lengthLabel_->setText(QString("Length (min): %1").arg(movie->getLength()));
  } else {
    lengthLabel_->setText("Length (min): ");
  }

  // Controllo universe vuoto o stringa base
  QString universe = QString::fromStdString(movie->getUniverse());
  if (!universe.isEmpty()) {
    universeLabel_->setText(QString("Universe: %1").arg(universe));
  } else {
    universeLabel_->setText("Universe: ");
  }

  // Cast: se vuoto, campo vuoto
  const auto& cast = movie->getCast();
  if (!cast.empty()) {
    QStringList castList;
    for (const auto& actor : cast) {
      castList << QString::fromStdString(actor);
    }
    castLabel_->setText(QString("Cast: %1").arg(castList.join(", ")));
  } else {
    castLabel_->setText("Cast: ");
  }
}


}  // namespace gui
