#include "ClickableFrame.h"

#include <QMouseEvent>

namespace gui {

ClickableFrame::ClickableFrame(QWidget* parent) : QFrame(parent) { setAttribute(Qt::WA_Hover); }

void ClickableFrame::mouseDoubleClickEvent(QMouseEvent* event) {
  emit doubleClicked();
  QFrame::mouseDoubleClickEvent(event);
}

void ClickableFrame::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::MouseButton::LeftButton) emit singleClicked();
  QFrame::mousePressEvent(event);
}

}  // namespace gui
