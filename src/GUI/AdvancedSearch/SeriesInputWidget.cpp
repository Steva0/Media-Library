#include "SeriesInputWidget.h"

#include "InputWidget.h"
#include <QLabel>

namespace gui {
namespace advanced_search {
SeriesInputWidget::SeriesInputWidget(QWidget *parent) : MovieInputWidget(parent) {
  ended_ = new QCheckBox(this);

  movie_layout_->addWidget(new QLabel("Terminata:", this), 0, movie_layout_->columnCount());
  movie_layout_->addWidget(ended_, 0, movie_layout_->columnCount());
}
// media::Series *SeriesInputWidget::getFilter() const {
//   auto *movie = MovieInputWidget::getFilter();
//   auto *series = new media::Series(*movie);
//   delete movie;

//   series->setEnded(ended_->isChecked());

//   return series;
// }
void SeriesInputWidget::makeFilterFor(InputWidget &other) const {
  other.makeFilterFrom(*this);
}
void SeriesInputWidget::setFromMedia(const media::Media &media) {
  MovieInputWidget::setFromMedia(media);
  if (const auto *series = dynamic_cast<const media::Series *>(&media)) {
    ended_->setChecked(series->hasEnded());
  }
}
bool SeriesInputWidget::getEnded() const { return ended_->isChecked(); }
}  // namespace advanced_search
}  // namespace gui
