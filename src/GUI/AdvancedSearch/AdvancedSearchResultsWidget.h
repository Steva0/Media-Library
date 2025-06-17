#ifndef GUI_ADVANCED_SEARCH_RESULTS_WIDGET
#define GUI_ADVANCED_SEARCH_RESULTS_WIDGET
#include "AdvancedSearchResultVisitor.h"
#include "../MainWindow.h"
#include "../../Media/Media.h"
namespace gui {
namespace advanced_search {
class AdvancedSearchResultsWidget : public QWidget {
  Q_OBJECT
private:
std::vector<QWidget *> search_results_;

public:
  explicit AdvancedSearchResultsWidget(QWidget *parent);
  
  void set_filter();
};
}
}  // namespace gui
#endif
