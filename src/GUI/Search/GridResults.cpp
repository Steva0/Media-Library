#include "GridResults.h"

#include <QVBoxLayout>

#include "../AdvancedSearch/ClickableFrame.h"
#include "SimpleResultVisitor.h"

namespace gui {
namespace search {

const int GridResults::kResultsPerRow = 4;

GridResults::GridResults(QWidget *parent) : QFrame(parent), grid_(new QGridLayout(this)) {
  grid_->setSpacing(0);
  updateResults(std::vector<const media::Media *>{});
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
  int max_height = -1;

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

    grid_->addWidget(wrapper, count / kResultsPerRow, count % kResultsPerRow);
    // wrapper->setMaximumHeight(wrapper->sizeHint().height());
    wrapper->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    max_height = std::max(max_height, wrapper->sizeHint().height());

    // Connetti con lambda che emette il media specifico
    connect(wrapper, &ClickableFrame::doubleClicked, this, [this, media]() { emit mediaDoubleClicked(media); });
    connect(wrapper, &ClickableFrame::singleClicked, [this, media]() { emit mediaSingleClicked(media); });

    ++count;
  }
  while (count > 0) {
    --count;
    QWidget *widget = grid_->itemAtPosition(count / kResultsPerRow, count % kResultsPerRow)->widget();
    widget->setMaximumHeight(max_height);

  }
  // while (count > 0) {
  //   --count;
  //   QWidget *widget = grid_->itemAtPosition(count / kResultsPerRow, count % kResultsPerRow)->widget();
  //   max_height = std::max(max_height, widget->sizeHint().height());
  //   if (count % kResultsPerRow == 0) {
  //     for (int i = 0; i < kResultsPerRow; ++i) {
  //       QWidget *to_update = grid_->itemAtPosition((count + i) / kResultsPerRow, (count + i) / kResultsPerRow)->widget();
  //       to_update->setMaximumHeight(max_height);
  //       count = -1;
        
  //     }
  //   }
  // }
}

}  // namespace search
}  // namespace gui
