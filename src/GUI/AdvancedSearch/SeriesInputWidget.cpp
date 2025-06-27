#include "SeriesInputWidget.h"
#include <QLabel>
#include <iostream>

namespace gui {
namespace advanced_search {
SeriesInputWidget::SeriesInputWidget(QWidget *parent) : MovieInputWidget(parent) {
  ended_ = new QCheckBox(this);
  
  layout_->addWidget(new QLabel("Ended:", this), 0, layout_->columnCount());
  layout_->addWidget(ended_, 0, layout_->columnCount());
}
media::Series *SeriesInputWidget::getFilter(const media::Media &base) const {
  auto *movie = MovieInputWidget::getFilter(base);
  auto *series = new media::Series(*movie);
  delete movie;

  series->setEnded(ended_->isChecked());
  
  return series;
}
}  // namespace advanced_search
}  // namespace gui
