#ifndef GUI_MEDIADETAILS_NOVELDETAILWIDGET_H
#define GUI_MEDIADETAILS_NOVELDETAILWIDGET_H

#include "MediaDetailWidget.h"
#include "../../Media/Novel.h"

#include <QLabel>
#include <QWidget>

namespace gui {

class NovelDetailWidget : public MediaDetailWidget {
  Q_OBJECT
public:
  explicit NovelDetailWidget(QWidget* parent = nullptr);

  void setMedia(const media::Media* media) override;

private:
  QLabel* authorLabel_;
  QLabel* publisherLabel_;
  QLabel* pagesLabel_;
  QLabel* seriesLabel_;
  QLabel* isbnLabel_;
};

}  // namespace gui

#endif  // GUI_MEDIADETAILS_NOVELDETAILWIDGET_H
