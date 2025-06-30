#ifndef GUI_CLICKABLE_FRAME_H
#define GUI_CLICKABLE_FRAME_H

#include <QFrame>

namespace gui {

class ClickableFrame : public QFrame {
  Q_OBJECT

 public:
  explicit ClickableFrame(QWidget* parent = nullptr);

 signals:
  void doubleClicked();
  void singleClicked();

 protected:
  void mouseDoubleClickEvent(QMouseEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
};

}  // namespace gui

#endif  // GUI_CLICKABLE_FRAME_H
