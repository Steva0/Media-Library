#include "SearchWidget.h"

namespace gui {
namespace search {
SearchWidget::SearchWidget(QWidget *parent)
    : QWidget(parent), input_(new InputBar(this)), advanced_search_(new QPushButton(this)) {
  connect(input_, &InputBar::timedEdit, this, &SearchWidget::searchByName);
  connect(advanced_search_, &QAbstractButton::clicked, this, &SearchWidget::openAdvancedSearch);
}
}  // namespace search
}  // namespace gui
