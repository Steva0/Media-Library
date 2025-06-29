#include "GridResults.h"
#include "../AdvancedSearch/ClickableFrame.h"
#include "SimpleResultVisitor.h"

#include <QVBoxLayout>

namespace gui {
namespace search {

const int GridResults::kResultPerRow = 4;

GridResults::GridResults(QWidget *parent)
    : QFrame(parent), grid_(new QGridLayout(this)) {
  grid_->setSpacing(0);
  updateResults(std::vector<const media::Media*>{});
  
}

void GridResults::updateResults(const std::vector<const media::Media *> &results) {
  // Pulisci il layout esistente
  while (QLayoutItem *item = grid_->takeAt(0)) {
    if (QWidget *widget = item->widget()) {
      grid_->removeWidget(widget);
      widget->deleteLater();
    }
    delete item;
  }

  
  results_ = results;  // salva internamente se serve
  int count = 0;
  
  for (const auto *media : results) {
    auto *wrapper = new ClickableFrame(this);
    wrapper->setFrameShape(QFrame::Box);
    auto *layout = new QVBoxLayout(wrapper);
    layout->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    SimpleResultVisitor v;
    media->accept(v);
    QWidget *result = v.getWidget();

    result->setParent(wrapper);
    layout->addWidget(result);

    grid_->addWidget(wrapper, count / kResultPerRow, count % kResultPerRow);
    wrapper->setMaximumHeight(wrapper->sizeHint().height());
    wrapper->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    
    // Connetti con lambda che emette il media specifico
    connect(wrapper, &ClickableFrame::doubleClicked, this, [this, media]() {
      emit mediaDoubleClicked(media);
    });
    connect(wrapper, &ClickableFrame::singleClicked, [this, media]() { emit mediaSingleClicked(media); });
    
    ++count;
  }
}

}  // namespace search
}  // namespace gui
