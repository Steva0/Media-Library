#include "TypeSelector.h"

#include <QHBoxLayout>

#include "../../Memory/Database.h"

namespace gui {
namespace advanced_search {

TypeSelector::TypeSelector(QWidget *parent) : QWidget(parent) {
  using MediaType = memory::Database::Type;

  auto *layout = new QHBoxLayout(this);
  container_ = new QButtonGroup(this);
  container_->setExclusive(true);

  layout->addStretch();

  int max_width = -1;
  for (size_t type = 0; type < static_cast<size_t>(MediaType::TypeFilterCount); ++type) {
    types_[type] = new QPushButton(QString::fromStdString(memory::Database::typeToString(type)), this);
    types_[type]->setCheckable(true);
    max_width = std::max(max_width, types_[type]->sizeHint().width());
    layout->addWidget(types_[type]);
    container_->addButton(types_[type]);
    container_->setId(types_[type], type);
  }
  types_[0]->setChecked(true);

  for (auto &type : types_) {
    type->setFixedWidth(max_width);
  }

  layout->addStretch();

  layout->setSpacing(0);

  connect(container_, &QButtonGroup::idClicked, this, &TypeSelector::selectType);
}
}  // namespace advanced_search
}  // namespace gui
