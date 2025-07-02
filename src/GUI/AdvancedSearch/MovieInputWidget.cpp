#include "MovieInputWidget.h"

#include <QLabel>
#include <limits>
#include "InputWidget.h"

#include "../../Media/Movie.h"
#include "MediaInputWidget.h"

namespace gui {
namespace advanced_search {
MovieInputWidget::MovieInputWidget(QWidget *parent) : MediaInputWidget(parent), movie_layout_(new QGridLayout) {
  actor_ = new QLineEdit(this);
  universe_ = new QLineEdit(this);

  // movie_layout_ = new QGridLayout(this);

  movie_layout_->addWidget(new QLabel("Attori:", this), 0, 0);
  movie_layout_->addWidget(actor_, 0, 1);

  movie_layout_->addWidget(new QLabel("Universo:", this), 0, 2);
  movie_layout_->addWidget(universe_, 0, 3);

  container_->addLayout(movie_layout_);
}
// media::Movie *MovieInputWidget::getFilter() const {
//   media::Media *base = MediaInputWidget::getFilter();
//   auto *movie = new media::Movie(*base);
//   delete base;

//   movie->addActor(actor_->text().toStdString());
//   movie->setUniverse(universe_->text().toStdString());

//   return movie;
// }
void MovieInputWidget::makeFilterFor(InputWidget &other) const {
  other.makeFilterFrom(*this);
}
void MovieInputWidget::setFromMedia(const media::Media &media) {
  MediaInputWidget::setFromMedia(media);
  if (const auto *movie = dynamic_cast<const media::Movie *>(&media)) {
    if (movie->getCast().size() != 0) actor_->setText(QString::fromStdString(movie->getCast()[0]));
    universe_->setText(QString::fromStdString(movie->getUniverse()));
  }
}
std::string MovieInputWidget::getActor() const { return actor_->text().toStdString(); }
std::string MovieInputWidget::getUniverse() const { return universe_->text().toStdString(); }

}  // namespace advanced_search
}  // namespace gui
