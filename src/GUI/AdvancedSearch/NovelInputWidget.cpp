#include "NovelInputWidget.h"

#include <QGridLayout>
#include <QLabel>
#include <limits>

#include "../../Media/Novel.h"
#include "MediaInputWidget.h"

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

media::Novel *NovelInputWidget::getFilter() const {
  media::Media *media = MediaInputWidget::getFilter();
  auto *novel = new media::Novel(*media);
  delete media;

  novel->setAuthor(author_->text().toStdString());
  novel->setPublisher(publisher_->text().toStdString());
  novel->setSeries(series_->text().toStdString());
  novel->setIsbn(isbn_->text().toStdString());
  return novel;
}
}  // namespace advanced_search
}  // namespace gui
