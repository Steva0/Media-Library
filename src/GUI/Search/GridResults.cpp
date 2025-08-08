#include <QLabel>
#include <QVBoxLayout>

#include "../ClickableFrame.h"
#include "GridResults.h"

namespace gui {
namespace search {

const int GridResults::kResultsPerRow = 4;

GridResults::GridResults(QWidget *parent) : QFrame(parent), grid_(new QGridLayout(this)) {
  grid_->setSpacing(0);
  updateResults({});
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

    QWidget *result = makeResult(*media);

    result->setParent(wrapper);
    layout->addWidget(result);

    grid_->addWidget(wrapper, count / kResultsPerRow, count % kResultsPerRow);
    wrapper->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    max_height = std::max(max_height, wrapper->sizeHint().height());

    // Connetti con lambda che emette il media specifico
    connect(wrapper, &ClickableFrame::doubleClicked, this, [this, media]() { emit mediaDoubleClicked(media); });
    connect(wrapper, &ClickableFrame::singleClicked, this, [this, media]() { emit mediaSingleClicked(media); });

    ++count;
  }
  while (count > 0) {
    --count;
    QWidget *widget = grid_->itemAtPosition(count / kResultsPerRow, count % kResultsPerRow)->widget();
    widget->setMaximumHeight(max_height);
  }
}

QWidget *GridResults::makeResult(const media::Media &media) {
  auto *result = new QWidget;
  auto *layout = new QVBoxLayout(result);

  auto *type = new QLabel(QString::fromStdString(media.displayType()), result);
  type->setAlignment(Qt::AlignCenter);

  auto *image = new QLabel(result);
  if (media.getImgPath() == "" || QPixmap(QString::fromStdString(media.getImgPath())).isNull())
    image->setPixmap(QPixmap(QString::fromStdString(":/assets/matita.jpg")).scaled(128, 128, Qt::KeepAspectRatio));
  else {
    image->setPixmap(QPixmap(QString::fromStdString(media.getImgPath())).scaled(128, 128, Qt::KeepAspectRatio));
  }
  image->setAlignment(Qt::AlignCenter);

  auto *title = new QLabel(QString::fromStdString(media.getTitle()), result);
  title->setAlignment(Qt::AlignCenter);

  layout->addWidget(type);
  layout->addStretch();
  layout->addWidget(image);
  layout->addStretch();
  layout->addWidget(title);

  return result;
}

}  // namespace search
}  // namespace gui
