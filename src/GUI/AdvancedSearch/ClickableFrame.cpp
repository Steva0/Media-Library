#include "ClickableFrame.h"
#include <QMouseEvent>

namespace gui {

ClickableFrame::ClickableFrame(QWidget* parent) : QFrame(parent) {
  setAttribute(Qt::WA_Hover);
}

void ClickableFrame::mouseDoubleClickEvent(QMouseEvent* event) {
  emit doubleClicked();
  QFrame::mouseDoubleClickEvent(event);
}

}  // namespace gui
