#include "AlbumInputWidget.h"
#include <QGridLayout>
#include <QLabel>
#include "../../Media/Album.h"

namespace gui {
namespace advanced_search {
AlbumInputWidget::AlbumInputWidget(QWidget *parent) : IMediaInputWidget(parent) {
  band_name_ = new QLineEdit(this);
  band_member_ = new QLineEdit(this);
  song_ = new QLineEdit(this);

  auto *layout = new QGridLayout(this);

  layout->addWidget(new QLabel("Band:", this), 0, 0);
  layout->addWidget(band_name_, 0, 1);

  layout->addWidget(new QLabel("Member:", this), 1, 0);
  layout->addWidget(band_member_, 1, 1);

  layout->addWidget(new QLabel("Song:", this), 2, 0);
  layout->addWidget(song_, 2, 1);
}

media::Album *AlbumInputWidget::getFilter(const media::Media &base) const {
  auto *album = new media::Album(base);
  album->setBand(band_name_->text().toStdString());
  album->addMember(band_member_->text().toStdString());
  album->addSong(song_->text().toStdString());
  return album;
}
}  // namespace advanced_search
}  // namespace gui
