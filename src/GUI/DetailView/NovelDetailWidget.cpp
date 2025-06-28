#include "NovelDetailWidget.h"
#include <limits>

namespace gui {

NovelDetailWidget::NovelDetailWidget(QWidget* parent) : MediaDetailWidget(parent) {
  authorLabel_ = new QLabel("Author: ", this);
  leftLayout_->addWidget(authorLabel_);

  publisherLabel_ = new QLabel("Publisher: ", this);
  leftLayout_->addWidget(publisherLabel_);

  pagesLabel_ = new QLabel("Pages: ", this);
  leftLayout_->addWidget(pagesLabel_);

  seriesLabel_ = new QLabel("Series: ", this);
  leftLayout_->addWidget(seriesLabel_);

  isbnLabel_ = new QLabel("ISBN: ", this);
  leftLayout_->addWidget(isbnLabel_);
}

void NovelDetailWidget::setMedia(const media::Media* media) {
  MediaDetailWidget::setMedia(media);

  const media::Novel* novel = dynamic_cast<const media::Novel*>(media);
  if (!novel) {
    authorLabel_->setText("Author: ");
    publisherLabel_->setText("Publisher: ");
    pagesLabel_->setText("Pages: ");
    seriesLabel_->setText("Series: ");
    isbnLabel_->setText("ISBN: ");
    return;
  }

  QString author = QString::fromStdString(novel->getAuthor());
  authorLabel_->setText(!author.isEmpty() ? QString("Author: %1").arg(author) : "Author: ");

  QString publisher = QString::fromStdString(novel->getPublisher());
  publisherLabel_->setText(!publisher.isEmpty() ? QString("Publisher: %1").arg(publisher) : "Publisher: ");

  int pages = novel->getPages();
  if (pages != std::numeric_limits<int>::min() && pages > 0) {
    pagesLabel_->setText(QString("Pages: %1").arg(pages));
  } else {
    pagesLabel_->setText("Pages: ");
  }

  QString series = QString::fromStdString(novel->getSeries());
  seriesLabel_->setText(!series.isEmpty() ? QString("Series: %1").arg(series) : "Series: ");

  QString isbn = QString::fromStdString(novel->getIsbn());
  isbnLabel_->setText(!isbn.isEmpty() ? QString("ISBN: %1").arg(isbn) : "ISBN: ");
}


}  // namespace gui
