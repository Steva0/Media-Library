#include "SelectedPreview.h"

#include "../PreviewVisitor.h"

namespace gui {
namespace search {
SelectedPreview::SelectedPreview(QWidget *parent)
    : QWidget(parent), layout_(new QHBoxLayout(this)), buttons_(new QWidget(this)), displayed_result_(nullptr) {
  auto *edit_button = new QPushButton("Edit", this);
  auto *delete_button = new QPushButton("Delete", this);

  edit_button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  delete_button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

  auto *buttons_layout = new QVBoxLayout(buttons_);
  buttons_layout->setAlignment(Qt::AlignRight);
  buttons_layout->addWidget(edit_button);
  buttons_layout->addStretch();
  buttons_layout->addWidget(delete_button);

  layout_->insertWidget(1, buttons_);
  buttons_->hide();

  connect(edit_button, &QAbstractButton::clicked, this, [&]() {
    if (selected_) emit editPressed(selected_);
  });
  connect(delete_button, &QAbstractButton::pressed, this, [&]() {
    if (selected_) emit deletePressed(selected_);
  });
}

void SelectedPreview::display(const media::Media *media) {
  if (displayed_result_) {
    layout_->removeWidget(displayed_result_);
    displayed_result_->deleteLater();
    delete displayed_result_;
  }
  if (buttons_->isHidden()) buttons_->show();

  if (!media) return;
  if (media != selected_) selected_ = media;

  PreviewVisitor v;
  media->accept(v);
  displayed_result_ = v.getWidget();
  layout_->insertWidget(0, displayed_result_);
}

void SelectedPreview::clear() { display(nullptr); }

}  // namespace search
}  // namespace gui
