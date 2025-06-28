#include "SearchWidget.h"

#include <QHBoxLayout>

#include "qsizepolicy.h"

namespace gui {
namespace search {
SearchWidget::SearchWidget(QWidget *parent)
    : QWidget(parent), input_(new InputBar(this)), advanced_search_(new QPushButton("Advanced", this)) {
  auto *layout = new QHBoxLayout(this);

  input_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  advanced_search_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

  layout->addWidget(advanced_search_);
  layout->addWidget(input_);

  layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

  connect(input_, &InputBar::timedEdit, this, &SearchWidget::searchByName);
  connect(advanced_search_, &QAbstractButton::clicked, this, &SearchWidget::openAdvancedSearch);
  connect(advanced_search_, &QPushButton::clicked, this, &SearchWidget::advancedClicked);

}
}  // namespace search
}  // namespace gui
