#ifndef GUI_MEDIADETAILS_SERIESDETAILWIDGET_H
#define GUI_MEDIADETAILS_SERIESDETAILWIDGET_H

#include <QLabel>

#include "../../Media/Series.h"
#include "MovieDetailWidget.h"

namespace gui {

class SeriesDetailWidget : public MovieDetailWidget {
  Q_OBJECT
 public:
  explicit SeriesDetailWidget(QWidget* parent = nullptr);

  void setMedia(const media::Media* media) override;

 private:
  QLabel* episodesLabel_;
  QLabel* seasonsLabel_;
  QLabel* endedLabel_;
};

}  // namespace gui

#endif  // GUI_MEDIADETAILS_SERIESDETAILWIDGET_H
