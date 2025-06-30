#include "AlbumInputWidget.h"

#include <QGridLayout>
#include <QLabel>

#include "../../Media/Album.h"
#include "MediaInputWidget.h"

namespace gui {
namespace advanced_search {
AlbumInputWidget::AlbumInputWidget(QWidget *parent) : MediaInputWidget(parent) {
  band_name_ = new QLineEdit(this);
  band_member_ = new QLineEdit(this);
  song_ = new QLineEdit(this);

  album_layout_ = new QGridLayout;

  album_layout_->addWidget(new QLabel("Band:", this), 0, 0);
  album_layout_->addWidget(band_name_, 0, 1);

  album_layout_->addWidget(new QLabel("Member:", this), 1, 0);
  album_layout_->addWidget(band_member_, 1, 1);

  album_layout_->addWidget(new QLabel("Song:", this), 2, 0);
  album_layout_->addWidget(song_, 2, 1);

  container_->addLayout(album_layout_);
}

media::Album *AlbumInputWidget::getFilter() const {
  media::Media *media = MediaInputWidget::getFilter();
  auto *album = new media::Album(*media);
  delete media;

  album->setBand(band_name_->text().toStdString());
  album->addMember(band_member_->text().toStdString());
  album->addSong(song_->text().toStdString());
  return album;
}
void AlbumInputWidget::setFromMedia(const media::Media &media) {
  MediaInputWidget::setFromMedia(media);
  if (const auto *album = dynamic_cast<const media::Album *>(&media)) {
    band_name_->setText(QString::fromStdString(album->getBand()));
    if (album->getBandMembers().size() != 0) band_member_->setText(QString::fromStdString(album->getBandMembers()[0]));
    if (album->getSongs().size() != 0) song_->setText(QString::fromStdString(album->getSongs()[0]));
  }
}
}  // namespace advanced_search
}  // namespace gui
