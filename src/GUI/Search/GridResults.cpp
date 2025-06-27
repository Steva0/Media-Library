#include "GridResults.h"

#include "SimpleResultVisitor.h"
#include "qnamespace.h"

namespace gui {
namespace search {
GridResults::GridResults(QWidget *parent) : QFrame(parent), grid_(new QGridLayout(this)) { grid_->setSpacing(0); }
void GridResults::updateResults(const std::vector<const media::Media *> &results) {
  while (QLayoutItem *item = grid_->takeAt(0)) {
    QWidget *widget = item->widget();
    grid_->removeWidget(widget);
    widget->deleteLater();
    delete widget;
  }

  int count = 0;
  for (const auto *media : results) {
    auto *wrapper = new QFrame(this);
    wrapper->setFrameShape(QFrame::Box);
    auto *layout = new QVBoxLayout(wrapper);
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    SimpleResultVisitor v;
    media->accept(v);
    QWidget *result = v.getResult();

    result->setParent(wrapper);
    layout->addWidget(result);

    grid_->addWidget(wrapper, count / 4, count % 4);
    wrapper->setMaximumHeight(wrapper->sizeHint().height());
    wrapper->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    ++count;
  }
}
}  // namespace search
}  // namespace gui
