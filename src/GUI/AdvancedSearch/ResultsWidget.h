#ifndef GUI_ADVANCED_SEARCH_RESULTS_WIDGET
#define GUI_ADVANCED_SEARCH_RESULTS_WIDGET
#include <QGridLayout>
#include <QScrollArea>

#include "../../Media/Media.h"

namespace gui {
namespace advanced_search {
class ResultsWidget : public QWidget {
  Q_OBJECT
  signals:
  void mediaDoubleClicked(const media::Media *media);
 private:
  QGridLayout *grid_;

  std::vector<const media::Media *> results_;

 public:
  explicit ResultsWidget(QWidget *parent);

  void updateResults(const std::vector<const media::Media *> &);
};
}  // namespace advanced_search
}  // namespace gui
#endif
