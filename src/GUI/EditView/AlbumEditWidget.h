#ifndef GUI_MEDIAEDIT_ALBUMEDITWIDGET_H
#define GUI_MEDIAEDIT_ALBUMEDITWIDGET_H

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <vector>

#include "MediaEditWidget.h"

namespace gui {

class AlbumEditWidget : public MediaEditWidget {
  Q_OBJECT
 public:
  explicit AlbumEditWidget(QWidget* parent = nullptr);

  void setMedia(const media::Media* media) override;
  media::Media* getModifiedMedia(bool old = true) const override;
  void clearInputFields() override;

 private:
  // Band
  QLineEdit* band_input_;

  // Band members
  QLineEdit* band_member_input_;
  QPushButton* add_band_member_button_;
  QGridLayout* band_members_layout_;
  std::vector<QLineEdit*> band_member_edits_;

  // Songs
  QLineEdit* song_input_;
  QPushButton* add_song_button_;
  QGridLayout* songs_layout_;
  std::vector<QLineEdit*> song_edits_;

  void addBandMember();
  void removeBandMember(QLineEdit* member_edit);

  void addSong();
  void removeSong(QLineEdit* song_edit);
};

}  // namespace gui

#endif  // GUI_MEDIAEDIT_ALBUMEDITWIDGET_H
