#include "ResultsWidget.h"

#include <memory>

#include "ResultVisitor.h"
#include "qgridlayout.h"
#include "qscrollarea.h"

namespace gui {
namespace advanced_search {
ResultsWidget::ResultsWidget(
    MainWindow *main_window)
    : QWidget(main_window), main_window_(*main_window) {}

void ResultsWidget::finalizeSearch(/* const std::vector<const media::Media *> &results */) {
  results_ = main_window_.filter(*filter_);

  // todo rimuovere results_widget_ che è ridondante
  scroll_area_ = new QScrollArea(this);
  results_widget_ = new QWidget(this);
  auto *grid = new QGridLayout(results_widget_);

  size_t pos = 0;

  for (auto &result : results_) {
    ResultVisitor v;
    result->accept(v);
    grid->addWidget(v.getResult(), pos / 2, pos % 2);
    ++pos;
  }


  scroll_area_->setWidget(results_widget_);
  scroll_area_->setMinimumWidth(results_widget_->width());
}

}  // namespace advanced_search
}  // namespace gui
