#include "ClickableFrame.h"

#include <QMouseEvent>
#include <QHoverEvent>
#include <QPalette>
#include <QCursor>
#include <QStyle>

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

bool ClickableFrame::event(QEvent* event) {
  if (event->type() == QEvent::HoverEnter) {
    QColor baseColor = palette().color(QPalette::Window);
    QColor darkerColor = baseColor.darker(110);  // 10% più scuro

    QPalette pal = palette();
    pal.setColor(QPalette::Window, darkerColor);
    setPalette(pal);
    setAutoFillBackground(true);
    update();
  } else if (event->type() == QEvent::HoverLeave) {
    QPalette pal = palette();
    pal.setColor(QPalette::Window, style()->standardPalette().color(QPalette::Window));
    setPalette(pal);
    update();
  }

  return QFrame::event(event);  // Continua con la gestione normale
}


}  // namespace gui
