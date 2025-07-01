#ifndef GUI_MEDIADETAILS_MOVIEDETAILWIDGET_H
#define GUI_MEDIADETAILS_MOVIEDETAILWIDGET_H

#include <QLabel>
#include <QListWidget>

#include "../../Media/Movie.h"
#include "MediaDetailWidget.h"

namespace gui {

class MovieDetailWidget : public MediaDetailWidget {
  Q_OBJECT
 public:
  explicit MovieDetailWidget(QWidget* parent = nullptr, bool note = true);

  void setMedia(const media::Media* media) override;
  void updateTextFontSize() override;

 private:
  QLabel* lengthLabel_;
  QLabel* universeLabel_;
  QLabel* castLabel_;
};

}  // namespace gui

#endif  // GUI_MEDIADETAILS_MOVIEDETAILWIDGET_H
