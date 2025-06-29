#ifndef GUI_ADVANCED_SEARCH_SERIES_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_SERIES_INPUT_WIDGET_H
#include <QCheckBox>

#include "../../Media/Series.h"
#include "MovieInputWidget.h"

namespace gui {
namespace advanced_search {
class SeriesInputWidget : public MovieInputWidget {
  Q_OBJECT
 private:
  QCheckBox *ended_;

 public:
  explicit SeriesInputWidget(QWidget *parent = nullptr);

  media::Series *getFilter() const override;
  void setFromMedia(const media::Media &) override;
};
}  // namespace advanced_search
}  // namespace gui
#endif
