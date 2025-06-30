#include "NovelInputWidget.h"

#include <QGridLayout>
#include <QLabel>
#include <limits>

#include "../../Media/Novel.h"
#include "MediaInputWidget.h"
#include "InputWidget.h"

namespace gui {
namespace advanced_search {
NovelInputWidget::NovelInputWidget(QWidget *parent)
    : MediaInputWidget(parent),
      author_(new QLineEdit(this)),
      publisher_(new QLineEdit(this)),
      series_(new QLineEdit(this)),
      isbn_(new QLineEdit(this)) {
  novel_layout_ = new QGridLayout;
  novel_layout_->addWidget(new QLabel("Author:", this), 0, 0);
  novel_layout_->addWidget(author_, 0, 1);

  novel_layout_->addWidget(new QLabel("Publisher:", this), 0, 2);
  novel_layout_->addWidget(publisher_, 0, 3);

  novel_layout_->addWidget(new QLabel("Series:", this), 1, 0);
  novel_layout_->addWidget(series_, 1, 1);

  novel_layout_->addWidget(new QLabel("ISBN:", this), 1, 2);
  novel_layout_->addWidget(isbn_, 1, 3);

  container_->addLayout(novel_layout_);
}

// media::Novel *NovelInputWidget::getFilter() const {
//   media::Media *media = MediaInputWidget::getFilter();
//   auto *novel = new media::Novel(*media);
//   delete media;

//   novel->setAuthor(author_->text().toStdString());
//   novel->setPublisher(publisher_->text().toStdString());
//   novel->setSeries(series_->text().toStdString());
//   novel->setIsbn(isbn_->text().toStdString());
//   return novel;
// }

void NovelInputWidget::makeFilterFor(InputWidget &other) const {
  other.makeFilterFrom(*this);
}
void NovelInputWidget::setFromMedia(const media::Media &media) {
  MediaInputWidget::setFromMedia(media);
  if (const auto *novel = dynamic_cast<const media::Novel *>(&media)) {
    author_->setText(QString::fromStdString(novel->getAuthor()));
    publisher_->setText(QString::fromStdString(novel->getPublisher()));
    series_->setText(QString::fromStdString(novel->getSeries()));
    isbn_->setText(QString::fromStdString(novel->getIsbn()));
  }
}
std::string NovelInputWidget::getAuthor() const { return author_->text().toStdString(); }
std::string NovelInputWidget::getPublisher() const { return publisher_->text().toStdString(); }
std::string NovelInputWidget::getSeries() const { return series_->text().toStdString(); }
std::string NovelInputWidget::getISBN() const { return isbn_->text().toStdString(); }
}  // namespace advanced_search
}  // namespace gui
