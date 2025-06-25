#ifndef GUI_ADVANCED_SEARCH_SERIES_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_SERIES_INPUT_WIDGET_H
#include <QCheckBox>

#include "MovieInputWidget.h"

namespace gui {
namespace advanced_search {
class SeriesInputWidget : public MovieInputWidget {
  Q_OBJECT
 private:
  QCheckBox *ended_;

 public:
  explicit SeriesInputWidget(QWidget *parent = nullptr);
};
}  // namespace advanced_search
}  // namespace gui
#endif
