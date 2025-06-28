#ifndef GUI_ADVANCED_SEARCH_TYPE_INPUT_BUILDER_H
#define GUI_ADVANCED_SEARCH_TYPE_INPUT_BUILDER_H
#include "MediaInputWidget.h"
namespace gui {
namespace advanced_search {
class TypeInputBuilder {
  Q_OBJECT
  public:
  static MediaInputWidget *buildWidgetFromType(int);
};
}  // namespace advanced_search
}  // namespace gui
#endif
