#include "MovieInputWidget.h"

#include <QLabel>
#include <limits>

#include "../../Media/Movie.h"

namespace gui {
namespace advanced_search {
MovieInputWidget::MovieInputWidget(QWidget *parent) : IMediaInputWidget(parent) {
  actor_ = new QLineEdit(this);
  universe_ = new QLineEdit(this);

  layout_ = new QGridLayout(this);

  layout_->addWidget(new QLabel("Actor:", this), 0, 0);
  layout_->addWidget(actor_, 0, 1);

  layout_->addWidget(new QLabel("Universe:", this), 0, 2);
  layout_->addWidget(universe_, 0, 3);
}
media::Movie *MovieInputWidget::getFilter(const media::Media &base) const {
  auto *movie = new media::Movie(media::Movie(base));
  movie->addActor(actor_->text().toStdString());
  movie->setUniverse(universe_->text().toStdString());
  
  return movie;
}
}  // namespace advanced_search
}  // namespace gui
