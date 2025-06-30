#include "EbookInputWidget.h"

#include <QLabel>
#include <iostream>
#include "InputWidget.h"

#include "../../Media/Ebook.h"

namespace gui {
namespace advanced_search {
EbookInputWidget::EbookInputWidget(QWidget *parent) : NovelInputWidget(parent) {
  drm_ = new QCheckBox(this);

  auto *last_item = novel_layout_->itemAtPosition(0, novel_layout_->columnCount() - 1);
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
// media::Ebook *EbookInputWidget::getFilter() const {
//   auto *novel = NovelInputWidget::getFilter();
//   auto *ebook = new media::Ebook(*novel);
//   delete novel;

//   ebook->setDrm(drm_->isChecked());
//   return ebook;
// }
void EbookInputWidget::makeFilterFor(InputWidget &other) const {
  other.makeFilterFrom(*this);
}
void EbookInputWidget::setFromMedia(const media::Media &media) {
  NovelInputWidget::setFromMedia(media);
  if (const auto *ebook = dynamic_cast<const media::Ebook *>(&media)) {
    drm_->setChecked(ebook->hasDrm());
  }
}
bool EbookInputWidget::getDRM() const { return drm_->isChecked(); }
}  // namespace advanced_search
}  // namespace gui
