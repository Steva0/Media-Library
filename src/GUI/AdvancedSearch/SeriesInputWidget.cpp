#include "SeriesInputWidget.h"
#include <QLabel>

namespace gui {
namespace advanced_search {
SeriesInputWidget::SeriesInputWidget(QWidget *parent) : MovieInputWidget(parent) {
  ended_ = new QCheckBox(this);
  
  layout_->addWidget(new QLabel("Ended:", this), 0, layout_->columnCount());
  layout_->addWidget(ended_, 0, layout_->columnCount());
}
}  // namespace advanced_search
}  // namespace gui
