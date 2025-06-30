#ifndef GUI_ADVANCED_SEARCH_IMEDIA_INPUT_WIDGET
#define GUI_ADVANCED_SEARCH_IMEDIA_INPUT_WIDGET
#include <QWidget>

#include "../../Media/Media.h"

namespace gui {
namespace advanced_search {
class InputWidget;
class IMediaInputWidget : public QWidget {
  Q_OBJECT
 public:
  explicit IMediaInputWidget(QWidget *parent = nullptr) : QWidget(parent) {}
  ~IMediaInputWidget() override = default;

  virtual void setFromMedia(const media::Media &) = 0;
  virtual void makeFilterFor(InputWidget &) const = 0;
};
}  // namespace advanced_search
}  // namespace gui
#endif
