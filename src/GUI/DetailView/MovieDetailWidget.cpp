#include "MovieDetailWidget.h"

#include <QString>

namespace gui {

MovieDetailWidget::MovieDetailWidget(QWidget* parent, bool note) : MediaDetailWidget(parent) {
  lengthLabel_ = new QLabel("Durata (min): ", this);
  universeLabel_ = new QLabel("Universo: ", this);
  castLabel_ = new QLabel("Cast: ", this);

  // Usa il leftLayout_ ereditato da MediaDetailWidget
  leftLayout_->addWidget(lengthLabel_);
  leftLayout_->addWidget(universeLabel_);
  leftLayout_->addWidget(castLabel_);

  if (note) {
    leftLayout_->addWidget(notesLabel_);
  }

  // Imposta il word wrap per le label aggiuntive
  lengthLabel_->setWordWrap(true);
  universeLabel_->setWordWrap(true);
  castLabel_->setWordWrap(true);
}

void MovieDetailWidget::setMedia(const media::Media* media) {
  MediaDetailWidget::setMedia(media);

  const media::Movie* movie = dynamic_cast<const media::Movie*>(media);
  if (!movie) {
    lengthLabel_->setText("Durata (min): ");
    universeLabel_->setText("Universo: ");
    castLabel_->setText("Cast: ");
    return;
  }

  // Controllo length, 0 o negativo lo considero "vuoto"
  if (movie->getLength() > 0) {
    lengthLabel_->setText(QString("Durata (min): %1").arg(movie->getLength()));
  } else {
    lengthLabel_->setText("Durata (min): ");
  }

  // Controllo universe vuoto o stringa base
  QString universe = QString::fromStdString(movie->getUniverse());
  if (!universe.isEmpty()) {
    universeLabel_->setText(QString("Universo: %1").arg(universe));
  } else {
    universeLabel_->setText("Universo: ");
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

void MovieDetailWidget::updateTextFontSize() {
  MediaDetailWidget::updateTextFontSize();  // Chiama la base per gestire le label comuni

  // Applica il font normale alle label aggiuntive
  lengthLabel_->setFont(normalLabelFont_);
  universeLabel_->setFont(normalLabelFont_);
  castLabel_->setFont(normalLabelFont_);
}

}  // namespace gui
