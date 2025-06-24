#ifndef GUI_ADVANCED_SEARCH_RESULTS_WIDGET
#define GUI_ADVANCED_SEARCH_RESULTS_WIDGET
#include <QScrollArea>
#include <memory>

#include "../../Media/Media.h"
#include "../MainWindow.h"

namespace gui {
namespace advanced_search {
class ResultsWidget : public QWidget {
  Q_OBJECT
 private:
  MainWindow &main_window_;

  QWidget *results_widget_;
  QScrollArea *scroll_area_;
  
  std::unique_ptr<media::Media> filter_;
  std::vector<const media::Media *> results_;

  void finalizeSearch();

 public:
  explicit ResultsWidget(MainWindow *main_window);

  // se ci serve dyn dispatch facciamo una versione per derivazione di Media
  template <typename T>
  void search(const T &filter) {
    filter_ = std::make_unique<T>(filter);
    finalizeSearch();
  }
};
}  // namespace advanced_search
}  // namespace gui
#endif
