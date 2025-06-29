#ifndef GUI_MEDIADETAILS_ALBUMDETAILWIDGET_H
#define GUI_MEDIADETAILS_ALBUMDETAILWIDGET_H

#include "MediaDetailWidget.h"
#include "../../Media/Album.h"

#include <QLabel>
#include <QWidget>
#include <QListWidget>

namespace gui {

class AlbumDetailWidget : public MediaDetailWidget {
  Q_OBJECT
public:
  explicit AlbumDetailWidget(QWidget* parent = nullptr);

  void setMedia(const media::Media* media) override;

private:
  QLabel* bandLabel_;
  QLabel* membersLabel_;
  QLabel* songsLabel_;
};

}  // namespace gui

#endif  // GUI_MEDIADETAILS_ALBUMDETAILWIDGET_H
