#ifndef GUI_MEDIADETAILS_AUDIOBOOKDETAILWIDGET_H
#define GUI_MEDIADETAILS_AUDIOBOOKDETAILWIDGET_H

#include <QLabel>

#include "../../Media/AudioBook.h"
#include "NovelDetailWidget.h"

namespace gui {

class AudioBookDetailWidget : public NovelDetailWidget {
  Q_OBJECT
 public:
  explicit AudioBookDetailWidget(QWidget* parent = nullptr);

  void setMedia(const media::Media* media) override;

 private:
  QLabel* narratorLabel_;
  QLabel* streamingServiceLabel_;
};

}  // namespace gui

#endif  // GUI_MEDIADETAILS_AUDIOBOOKDETAILWIDGET_H
