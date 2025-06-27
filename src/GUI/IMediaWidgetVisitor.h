#ifndef GUI_I_MEDIA_WIDGET_VISITOR_H
#define GUI_I_MEDIA_WIDGET_VISITOR_H

#include <QWidget>

#include "../Media/IConstMediaVisitor.h"

namespace gui {
class IMediaWidgetVisitor : public media::IConstMediaVisitor {
 public:
  virtual QWidget *getWidget() = 0;
};
}  // namespace gui

#endif
