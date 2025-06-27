#include "GridResults.h"

#include "SimpleResultVisitor.h"

namespace gui {
namespace search {
GridResults::GridResults(QWidget *parent) : QFrame(parent), grid_(new QGridLayout(this)) {}
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
    auto *layout = new QVBoxLayout(wrapper);
    wrapper->setFrameShape(QFrame::Box);

    SimpleResultVisitor v;
    media->accept(v);
    QWidget *result = v.getResult();

    result->setParent(wrapper);
    layout->addWidget(result);

    grid_->addWidget(result, count / 4, count % 4);
    ++count;
  }
}
}  // namespace search
}  // namespace gui
