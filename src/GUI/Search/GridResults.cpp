#include "GridResults.h"
#include "../AdvancedSearch/ClickableFrame.h"
#include "SimpleResultVisitor.h"

#include <QVBoxLayout>

namespace gui {
namespace search {

using gui::ClickableFrame;

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

    // Usa un segnale intermedio per passare il puntatore media
    connect(wrapper, &ClickableFrame::doubleClicked, this, &GridResults::onMediaDoubleClicked);

    ++count;
  }
}

void GridResults::onMediaDoubleClicked() {
  // Trova quale ClickableFrame ha emesso il segnale
  ClickableFrame* senderFrame = qobject_cast<ClickableFrame*>(sender());
  if (!senderFrame)
    return;

  // Trova l'indice del frame
  int index = -1;
  for (int i = 0; i < grid_->count(); ++i) {
    if (grid_->itemAt(i)->widget() == senderFrame) {
      index = i;
      break;
    }
  }
  if (index >= 0 && index < static_cast<int>(results_.size())) {
    emit mediaDoubleClicked(results_[index]);
  }
}

}  // namespace search
}  // namespace gui
