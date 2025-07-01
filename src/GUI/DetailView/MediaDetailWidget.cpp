#include "MediaDetailWidget.h"

#include <QHBoxLayout>
#include <QPixmap>
#include <QResizeEvent>
#include <QString>
#include <QVBoxLayout>

namespace gui {

MediaDetailWidget::MediaDetailWidget(QWidget* parent) : IMediaDetailWidget(parent), coverPixmap_() {
  auto* mainLayout = new QHBoxLayout(this);

  leftWidget_ = new QWidget(this);
  leftLayout_ = new QVBoxLayout(leftWidget_);
  leftWidget_->setLayout(leftLayout_);

  titleLabel_ = new QLabel(this);
  spacerLabel_ = new QLabel(this);  
  releaseLabel_ = new QLabel("Release year: ", this);
  languageLabel_ = new QLabel("Language: ", this);
  favouriteLabel_ = new QLabel("Favourite: ", this);
  genresLabel_ = new QLabel("Genres: ", this);
  notesLabel_ = new QLabel("Notes: ", this);

  leftLayout_->addWidget(titleLabel_);
  leftLayout_->addWidget(releaseLabel_);
  leftLayout_->addWidget(languageLabel_);
  leftLayout_->addWidget(favouriteLabel_);
  leftLayout_->addWidget(genresLabel_);

  mainLayout->addWidget(leftWidget_, 2, Qt::AlignTop);

  coverLabel_ = new QLabel(this);
  coverLabel_->setAlignment(Qt::AlignCenter);
  coverLabel_->setScaledContents(false);  // facciamo scalare a mano noi
  mainLayout->addWidget(coverLabel_, 1);

  releaseLabel_->setWordWrap(true);
  languageLabel_->setWordWrap(true);
  favouriteLabel_->setWordWrap(true);
  genresLabel_->setWordWrap(true);
  notesLabel_->setWordWrap(true);
}

void MediaDetailWidget::setMedia(const media::Media* media) {
  if (!media) {
    clearFields();
    return;
  }

  // Title: supponiamo non possa mai essere vuoto
  titleLabel_->setText(QString::fromStdString(media->getTitle()));

  // Release year: se uguale a valore base, campo vuoto
  int releaseYear = media->getRelease();
  if (releaseYear == std::numeric_limits<int>::min()) {
    releaseLabel_->setText("Release year: ");
  } else {
    releaseLabel_->setText(QString("Release year: %1").arg(releaseYear));
  }

  // Language: se stringa vuota o solo spazi, campo vuoto
  QString language = QString::fromStdString(media->getLanguage()).trimmed();
  if (language.isEmpty()) {
    languageLabel_->setText("Language: ");
  } else {
    languageLabel_->setText(QString("Language: %1").arg(language));
  }

  // Favourite: true/false, sempre visualizzato
  favouriteLabel_->setText(QString("Favourite: %1").arg(media->isFavourite() ? "Yes" : "No"));

  // Genres: se vuoto, campo vuoto
  const auto& genres = media->getGenres();
  if (genres.empty()) {
    genresLabel_->setText("Genres: ");
  } else {
    QStringList genresList;
    for (const auto& g : genres) {
      genresList << QString::fromStdString(g);
    }
    genresLabel_->setText(QString("Genres: %1").arg(genresList.join(", ")));
  }

  // Notes: se vuoto o solo spazi, campo vuoto
  QString notes = QString::fromStdString(media->getNotes()).trimmed();
  if (notes.isEmpty()) {
    notesLabel_->setText("Notes: ");
  } else {
    notesLabel_->setText(QString("Notes: %1").arg(notes));
  }

  // Carico immagine
  QPixmap pixmap(QString::fromStdString(media->getImgPath()));
  if (pixmap.isNull()) {
    pixmap = QPixmap(":/assets/matita.jpg");
  }
  coverPixmap_ = pixmap;

  updateCoverPixmap();
}

void MediaDetailWidget::clearFields() {
  titleLabel_->setText("");
  releaseLabel_->setText("Release year: ");
  languageLabel_->setText("Language: ");
  favouriteLabel_->setText("Favourite: ");
  genresLabel_->setText("Genres: ");
  notesLabel_->setText("Notes: ");

  coverPixmap_ = QPixmap(":/assets/matita.jpg");
  updateCoverPixmap();
}

void MediaDetailWidget::resizeEvent(QResizeEvent* event) {
  IMediaDetailWidget::resizeEvent(event);
  updateCoverPixmap();
  updateTextFontSize();
}

void MediaDetailWidget::updateCoverPixmap() {
  if (coverPixmap_.isNull()) {
    coverLabel_->clear();
    return;
  }

  // Calcolo la larghezza che la cover deve occupare (1/3 della larghezza del widget)
  int targetWidth = width() / 3;

  // Calcolo l'altezza mantenendo il rapporto d'aspetto
  int targetHeight = coverPixmap_.height() * targetWidth / coverPixmap_.width();

  // Ridimensiono e setto la pixmap
  coverLabel_->setPixmap(coverPixmap_.scaled(targetWidth, targetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MediaDetailWidget::updateTextFontSize() {
  if (!leftWidget_) return;

  int totalHeight = height();

  // Calcoliamo lo spazio per titolo e il resto
  int totalLabels = 6; // le etichette oltre al titolo
  int spaceForText = totalHeight * 0.9;

  int titleLabelFont_Size = std::clamp(spaceForText / 12, 16, 36);  // più grande
  int otherFontSize = std::clamp(spaceForText / (totalLabels * 2), 10, 24);  // più piccolo

  // Font titolo: grande e bold
  titleLabelFont_.setPointSize(titleLabelFont_Size);
  titleLabelFont_.setBold(true);
  titleLabel_->setFont(titleLabelFont_);

  // Font normale: più piccolo e non bold
  normalLabelFont_.setPointSize(otherFontSize);
  normalLabelFont_.setBold(false);

  releaseLabel_->setFont(normalLabelFont_);
  languageLabel_->setFont(normalLabelFont_);
  favouriteLabel_->setFont(normalLabelFont_);
  genresLabel_->setFont(normalLabelFont_);
  notesLabel_->setFont(normalLabelFont_);

  // La riga vuota può essere piccola o nulla
  spacerLabel_->setFixedHeight(titleLabelFont_Size / 2);
}


}  // namespace gui
