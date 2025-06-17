#ifndef GUI_ADVANCED_SEARCH_RESULTS_WIDGET
#define GUI_ADVANCED_SEARCH_RESULTS_WIDGET
#include <QScrollArea>
#include <memory>

#include "../../Media/Media.h"
#include "../MainWindow.h"
#include "AdvancedSearchResultVisitor.h"
namespace gui {
namespace advanced_search {
class AdvancedSearchResultsWidget : public QWidget {
  Q_OBJECT
 private:
  MainWindow &main_window_;

  QWidget *results_widget_;
  QScrollArea *scroll_area_;
  // per rifare facilmente query
  // puntatore per polimorfismo
  std::unique_ptr<media::Media> filter_;
  std::vector<const media::Media *> results_;

 public:
  explicit AdvancedSearchResultsWidget(MainWindow *main_window);
  void search(const media::Media &);
};
}  // namespace advanced_search
}  // namespace gui
#endif
