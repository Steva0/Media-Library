#ifndef GUI_MEDIADETAILS_IMEDIADETAILWIDGET_H
#define GUI_MEDIADETAILS_IMEDIADETAILWIDGET_H

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

#include "../../Media/Media.h"

namespace gui {

class IMediaDetailWidget : public QWidget {
  Q_OBJECT
 public:
  explicit IMediaDetailWidget(QWidget* parent = nullptr) : QWidget(parent) {}
  virtual ~IMediaDetailWidget() = default;

  virtual void setMedia(const media::Media* media) = 0;
  virtual void updateTextFontSize() = 0;
};

}  // namespace gui

#endif  // GUI_MEDIADETAILS_IMEDIADETAILWIDGET_H
