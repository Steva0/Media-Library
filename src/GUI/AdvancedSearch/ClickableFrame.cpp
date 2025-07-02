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

void ClickableFrame::hoverEnterEvent(QHoverEvent* event) {
  Q_UNUSED(event);
  // Ottieni il colore di base del sistema (es. background dei widget)
  QColor baseColor = palette().color(QPalette::Window);
  QColor darkerColor = baseColor.darker(110); // 110 = 10% più scuro

  QPalette pal = palette();
  pal.setColor(QPalette::Window, darkerColor);
  setPalette(pal);
  setAutoFillBackground(true); // obbligatorio per rendere visibile il colore
  update();
}

void ClickableFrame::hoverLeaveEvent(QHoverEvent* event) {
  Q_UNUSED(event);
  // Ripristina il colore originale
  QPalette pal = palette();
  pal.setColor(QPalette::Window, style()->standardPalette().color(QPalette::Window));
  setPalette(pal);
  update();
}

}  // namespace gui
