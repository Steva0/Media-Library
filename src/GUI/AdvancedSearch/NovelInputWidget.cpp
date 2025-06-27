#include "NovelInputWidget.h"

#include <QGridLayout>
#include <QLabel>
#include <limits>

#include "../../Media/Novel.h"
#include "MediaInputWidget.h"

namespace gui {
namespace advanced_search {
NovelInputWidget::NovelInputWidget(QWidget *parent)
    : IMediaInputWidget(parent),
      author_(new QLineEdit(this)),
      publisher_(new QLineEdit(this)),
      series_(new QLineEdit(this)),
      isbn_(new QLineEdit(this)) {
  layout_ = new QGridLayout(this);
  layout_->addWidget(new QLabel("Author:", this), 0, 0);
  layout_->addWidget(author_, 0, 1);

  layout_->addWidget(new QLabel("Publisher:", this), 0, 2);
  layout_->addWidget(publisher_, 0, 3);

  layout_->addWidget(new QLabel("Series:", this), 1, 0);
  layout_->addWidget(series_, 1, 1);

  layout_->addWidget(new QLabel("ISBN:", this), 1, 2);
  layout_->addWidget(isbn_, 1, 3);
}

media::Novel *NovelInputWidget::getFilter(const media::Media &base) const {
  auto *novel = new media::Novel(base);
  novel->setAuthor(author_->text().toStdString());
  novel->setPublisher(publisher_->text().toStdString());
  novel->setSeries(series_->text().toStdString());
  novel->setIsbn(isbn_->text().toStdString());

  return novel;
}
}  // namespace advanced_search
}  // namespace gui
