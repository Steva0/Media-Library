#include "SeriesInputWidget.h"
#include <QLabel>
#include <iostream>

namespace gui {
namespace advanced_search {
SeriesInputWidget::SeriesInputWidget(QWidget *parent) : MovieInputWidget(parent) {
  ended_ = new QCheckBox(this);
  
  movie_layout_->addWidget(new QLabel("Ended:", this), 0, movie_layout_->columnCount());
  movie_layout_->addWidget(ended_, 0, movie_layout_->columnCount());
}
media::Series *SeriesInputWidget::getFilter() const {
  auto *movie = MovieInputWidget::getFilter();
  auto *series = new media::Series(*movie);
  delete movie;

  series->setEnded(ended_->isChecked());
  
  return series;
}
}  // namespace advanced_search
}  // namespace gui
