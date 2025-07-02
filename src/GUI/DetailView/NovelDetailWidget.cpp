#include "NovelDetailWidget.h"
#include "../../Media/AudioBook.h"

#include <limits>

namespace gui {

NovelDetailWidget::NovelDetailWidget(QWidget* parent, bool note) : MediaDetailWidget(parent) {
  authorLabel_ = new QLabel("Autore: ", this);
  leftLayout_->addWidget(authorLabel_);

  publisherLabel_ = new QLabel("Casa editirice: ", this);
  leftLayout_->addWidget(publisherLabel_);

  pagesLabel_ = new QLabel("Pagine: ", this);
  leftLayout_->addWidget(pagesLabel_);

  seriesLabel_ = new QLabel("Collana: ", this);
  leftLayout_->addWidget(seriesLabel_);

  isbnLabel_ = new QLabel("ISBN: ", this);
  leftLayout_->addWidget(isbnLabel_);

  if (note) {
    leftLayout_->addWidget(notesLabel_);
  }

  // Imposta il word wrap per le label aggiuntive
  authorLabel_->setWordWrap(true);
  publisherLabel_->setWordWrap(true);
  pagesLabel_->setWordWrap(true);
  seriesLabel_->setWordWrap(true);
  isbnLabel_->setWordWrap(true);
}

void NovelDetailWidget::setMedia(const media::Media* media) {
  MediaDetailWidget::setMedia(media);

  const media::Novel* novel = dynamic_cast<const media::Novel*>(media);
  if (!novel) {
    authorLabel_->setText("Autore: ");
    publisherLabel_->setText("Casa editirice: ");
    pagesLabel_->setText("Pagine: ");
    seriesLabel_->setText("Collana: ");
    isbnLabel_->setText("ISBN: ");
    return;
  }

  QString author = QString::fromStdString(novel->getAuthor());
  authorLabel_->setText(!author.isEmpty() ? QString("Autore: %1").arg(author) : "Autore: ");

  QString publisher = QString::fromStdString(novel->getPublisher());
  publisherLabel_->setText(!publisher.isEmpty() ? QString("Casa editirice: %1").arg(publisher) : "Casa editirice: ");

  // Etichetta per durata se è un AudioBook
  const media::AudioBook* audioBook = dynamic_cast<const media::AudioBook*>(media);
  int pages = novel->getPages();
  if (audioBook) {
    pagesLabel_->setText(pages > 0 ? QString("Duration (min): %1").arg(pages) : "Duration (min): ");
  } else {
    pagesLabel_->setText(pages > 0 ? QString("Pagine: %1").arg(pages) : "Pagine: ");
  }

  QString series = QString::fromStdString(novel->getSeries());
  seriesLabel_->setText(!series.isEmpty() ? QString("Collana: %1").arg(series) : "Collana: ");

  QString isbn = QString::fromStdString(novel->getIsbn());
  isbnLabel_->setText(!isbn.isEmpty() ? QString("ISBN: %1").arg(isbn) : "ISBN: ");
}

void NovelDetailWidget::updateTextFontSize() {
  MediaDetailWidget::updateTextFontSize();  // Chiama la base per gestire le label comuni

  // Applica il font normale alle label aggiuntive
  authorLabel_->setFont(normalLabelFont_);
  publisherLabel_->setFont(normalLabelFont_);
  pagesLabel_->setFont(normalLabelFont_);
  seriesLabel_->setFont(normalLabelFont_);
  isbnLabel_->setFont(normalLabelFont_);
}

}  // namespace gui
