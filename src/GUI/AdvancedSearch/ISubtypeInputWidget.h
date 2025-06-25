#ifndef GUI_ADVANCED_SEARCH_ISUBTYPE_INPUT_WIDGET
#define GUI_ADVANCED_SEARCH_ISUBTYPE_INPUT_WIDGET
#include "../../Media/Media.h"

namespace gui {
namespace advanced_search {
class ISubtypeInputWidget {
 public:
  virtual media::Media *getFilter() const = 0;
};
}  // namespace advanced_search
}  // namespace gui
#endif
