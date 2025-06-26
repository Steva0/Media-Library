#include "TypeSelector.h"

#include <QHBoxLayout>

#include "../../Memory/MediaContainer.h"

namespace gui {
namespace advanced_search {

TypeSelector::TypeSelector(QWidget *parent) : QWidget(parent) {
  using MediaType = memory::MediaContainer::Type;

  auto *layout = new QHBoxLayout(this);
  container_ = new QButtonGroup(this);
  container_->setExclusive(true);

  layout->addStretch();

  int max_width = -1;
  for (size_t type = 0; type < static_cast<size_t>(MediaType::TypeCount); ++type) {
    types_[type] = new QPushButton(QString::fromStdString(memory::MediaContainer::typeToString(type)), this);
    max_width = std::max(max_width, types_[type]->sizeHint().width());
    layout->addWidget(types_[type]);
    container_->addButton(types_[type]);
    container_->setId(types_[type], type);
  }

  for (auto &type : types_) {
    type->setFixedWidth(max_width);
  }

  layout->addStretch();

  layout->setSpacing(0);

  connect(container_, &QButtonGroup::idClicked, this, &TypeSelector::selectType);
}
}  // namespace advanced_search
}  // namespace gui
