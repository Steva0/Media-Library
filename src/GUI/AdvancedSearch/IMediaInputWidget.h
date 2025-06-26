#ifndef GUI_ADVANCED_SEARCH_ISUBTYPE_INPUT_WIDGET
#define GUI_ADVANCED_SEARCH_ISUBTYPE_INPUT_WIDGET
#include <QWidget>

#include "../../Media/Media.h"

namespace gui {
namespace advanced_search {
class IMediaInputWidget : public QWidget {
  Q_OBJECT
 public:
  virtual media::Media *getFilter(const media::Media &base) const = 0;
  explicit IMediaInputWidget(QWidget *parent = nullptr) : QWidget(parent) {}
   ~IMediaInputWidget() override = default;
};
}  // namespace advanced_search
}  // namespace gui
#endif
