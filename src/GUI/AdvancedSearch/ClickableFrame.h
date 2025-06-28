#ifndef GUI_CLICKABLE_FRAME_H
#define GUI_CLICKABLE_FRAME_H

#include <QFrame>

namespace gui {
class ClickableFrame : public QFrame {
  Q_OBJECT
 public:
  explicit ClickableFrame(QWidget *parent = nullptr) : QFrame(parent) {
    setAttribute(Qt::WA_Hover);
  }

 signals:
  void doubleClicked();

 protected:
  void mouseDoubleClickEvent(QMouseEvent *event) override {
    emit doubleClicked();
    QFrame::mouseDoubleClickEvent(event);
  }
};
}  // namespace gui

#endif
