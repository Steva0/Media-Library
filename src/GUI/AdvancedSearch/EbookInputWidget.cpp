#include "EbookInputWidget.h"
#include <QLabel>
#include "../../Media/Ebook.h"

#include <iostream>

namespace gui {
namespace advanced_search {
EbookInputWidget::EbookInputWidget(QWidget *parent) : NovelInputWidget(parent) {
  drm_ = new QCheckBox(this);

  auto *last_item= novel_layout_->itemAtPosition(0, novel_layout_->columnCount() - 1);
  int last_idx = novel_layout_->indexOf(last_item);

  int row;
  int col;
  int row_span;
  int col_span;
  novel_layout_->getItemPosition(last_idx, &row, &col, &row_span, &col_span);
  novel_layout_->removeItem(last_item);

  novel_layout_->addItem(last_item, row, col, row_span, col_span + 2);
  novel_layout_->addWidget(new QLabel("DRM:", this), novel_layout_->rowCount() - 1, 4);
  novel_layout_->addWidget(drm_, novel_layout_->rowCount() - 1, 5);
}
media::Ebook *EbookInputWidget::getFilter() const {
  auto *novel = NovelInputWidget::getFilter();
  auto *ebook = new media::Ebook(*novel);
  delete novel;

  ebook->setDrm(drm_->isChecked());
  return ebook;
}
}  // namespace advanced_search
}  // namespace gui
