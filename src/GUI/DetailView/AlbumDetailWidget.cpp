#include "AlbumDetailWidget.h"

#include <QLabel>
#include <QStringList>

namespace gui {

AlbumDetailWidget::AlbumDetailWidget(QWidget* parent) : MediaDetailWidget(parent) {
  bandLabel_ = new QLabel("Band: ", this);
  leftLayout_->addWidget(bandLabel_);

  membersLabel_ = new QLabel("Band Members: ", this);
  leftLayout_->addWidget(membersLabel_);

  songsLabel_ = new QLabel("Songs: ", this);
  leftLayout_->addWidget(songsLabel_);
  
  leftLayout_->addWidget(notesLabel_);
}

void AlbumDetailWidget::setMedia(const media::Media* media) {
  MediaDetailWidget::setMedia(media);

  const media::Album* album = dynamic_cast<const media::Album*>(media);
  if (!album) {
    bandLabel_->setText("Band: ");
    membersLabel_->setText("Band Members: ");
    songsLabel_->setText("Songs: ");
    return;
  }

  const std::string& band = album->getBand();
  bandLabel_->setText(QString("Band: %1").arg(band.empty() ? "" : QString::fromStdString(band)));

  const auto& members = album->getBandMembers();
  if (members.empty()) {
    membersLabel_->setText("Band Members: ");
  } else {
    QStringList membersList;
    for (const auto& member : members) {
      membersList << QString::fromStdString(member);
    }
    membersLabel_->setText(QString("Band Members: %1").arg(membersList.join(", ")));
  }

  const auto& songs = album->getSongs();
  if (songs.empty()) {
    songsLabel_->setText("Songs: ");
  } else {
    QStringList songsList;
    for (const auto& song : songs) {
      songsList << QString::fromStdString(song);
    }
    songsLabel_->setText(QString("Songs: %1").arg(songsList.join(", ")));
  }
}

void AlbumDetailWidget::updateTextFontSize() {
  MediaDetailWidget::updateTextFontSize();  // chiama base

  bandLabel_->setFont(normalLabelFont_);
  membersLabel_->setFont(normalLabelFont_);
  songsLabel_->setFont(normalLabelFont_);
}

}// namespace gui
