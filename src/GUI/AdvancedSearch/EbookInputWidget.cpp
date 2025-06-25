#include "EbookInputWidget.h"

#include <iostream>

namespace gui {
namespace advanced_search {
EbookInputWidget::EbookInputWidget(QWidget *parent) : NovelInputWidget(parent) {
  // novel_ = new NovelInputWidget(this);
  drm_ = new QCheckBox(this);

  auto *last_item= layout_->itemAtPosition(0, layout_->columnCount() - 1);
  int last_idx = layout_->indexOf(last_item);

  int _row;
  int _col;
  int _row_span;
  int col_span;
  layout_->getItemPosition(last_idx, &_row, &_col, &_row_span, &col_span);
  layout_->removeItem(last_item);

  layout_->addItem(last_item, _row, _col, _row_span, col_span + 2);
  layout_->addWidget(new QLabel("DRM:", this), layout_->rowCount() - 1, 4);
  layout_->addWidget(drm_, layout_->rowCount() - 1, 5);
}
}  // namespace advanced_search
}  // namespace gui
