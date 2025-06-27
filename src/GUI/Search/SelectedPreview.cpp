#include "SelectedPreview.h"

#include "../PreviewVisitor.h"
#include "qboxlayout.h"

namespace gui {
namespace search {
SelectedPreview::SelectedPreview(QWidget *parent) : QWidget(parent), layout_(new QHBoxLayout(this)) {
  edit_ = new QPushButton(this);
  delete_ = new QPushButton(this);

  auto *button_layout = new QVBoxLayout;
  button_layout->addWidget(edit_);
  button_layout->addStretch();
  button_layout->addWidget(delete_);

  layout_->insertLayout(1, button_layout);

  connect(edit_, &QAbstractButton::clicked, this, &SelectedPreview::editMedia);
  connect(delete_, &QAbstractButton::clicked, this, &SelectedPreview::deleteMedia);
}

void SelectedPreview::display(const media::Media &media) {
  if (displayed_result_) {
    layout_->removeWidget(displayed_result_);
    displayed_result_->deleteLater();
    delete displayed_result_;
  }

  PreviewVisitor v;
  media.accept(v);
  displayed_result_ = v.getResult();
  layout_->insertWidget(0, displayed_result_);
}

}  // namespace search
}  // namespace gui
