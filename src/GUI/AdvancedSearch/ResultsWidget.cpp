#include "ResultsWidget.h"

#include "ResultVisitor.h"

namespace gui {
namespace advanced_search {
ResultsWidget::ResultsWidget(QWidget *parent) : QWidget(parent), grid_(new QGridLayout(this)) {}

void ResultsWidget::updateResults(const std::vector<const media::Media *> &new_results) {
  results_ = new_results;

  // clear
  while (grid_->count()) {
    QWidget *widget = grid_->takeAt(0)->widget();
    grid_->removeWidget(widget);
    delete widget;
  }

  size_t pos = 0;

  int last_height = -1;
  QWidget *last_widget;

  for (auto &result : results_) {
    ResultVisitor v;
    result->accept(v);
    auto *widget = v.getResult();
    widget->setParent(this);
    if (last_height == -1) {
      last_height = widget->sizeHint().height();
      last_widget = widget;
      widget->setFixedHeight(last_height);
    } else {
      last_height = std::max(last_height, widget->sizeHint().height());
      last_widget->setFixedHeight(last_height);
      widget->setFixedHeight(last_height);
      last_height = -1;
      last_widget = nullptr;
    }
    grid_->addWidget(widget, pos / 2, pos % 2);
    ++pos;
  }
}
}  // namespace advanced_search
}  // namespace gui
