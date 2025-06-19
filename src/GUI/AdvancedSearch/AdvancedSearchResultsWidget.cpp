#include "AdvancedSearchResultsWidget.h"

#include <memory>

#include "AdvancedSearchResultVisitor.h"
#include "qgridlayout.h"
#include "qscrollarea.h"

namespace gui {
namespace advanced_search {
AdvancedSearchResultsWidget::AdvancedSearchResultsWidget(
    MainWindow *main_window)
    : QWidget(main_window), main_window_(*main_window) {}

void AdvancedSearchResultsWidget::finalizeSearch() {
  results_ = main_window_.filter(*filter_);

  scroll_area_ = new QScrollArea(this);
  results_widget_ = new QWidget(this);
  auto *grid = new QGridLayout(results_widget_);

  size_t pos = 0;

  for (auto &result : results_) {
    AdvancedSearchResultVisitor v;
    result->accept(v);
    grid->addWidget(v.getResult(), pos / 2, pos % 2);
    ++pos;
  }


  scroll_area_->setWidget(results_widget_);
  scroll_area_->setMinimumWidth(results_widget_->width());
}

}  // namespace advanced_search
}  // namespace gui
