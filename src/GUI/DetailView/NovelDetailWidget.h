#ifndef GUI_MEDIADETAILS_NOVELDETAILWIDGET_H
#define GUI_MEDIADETAILS_NOVELDETAILWIDGET_H

#include <QLabel>
#include <QWidget>

#include "../../Media/Novel.h"
#include "MediaDetailWidget.h"

namespace gui {

class NovelDetailWidget : public MediaDetailWidget {
  Q_OBJECT
 public:
  explicit NovelDetailWidget(QWidget* parent = nullptr, bool note = true);

  void setMedia(const media::Media* media) override;
  void updateTextFontSize() override;

 private:
  QLabel* authorLabel_;
  QLabel* publisherLabel_;
  QLabel* pagesLabel_;
  QLabel* seriesLabel_;
  QLabel* isbnLabel_;
};

}  // namespace gui

#endif  // GUI_MEDIADETAILS_NOVELDETAILWIDGET_H
