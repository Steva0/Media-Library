#include "SelectedPreview.h"

#include "../PreviewVisitor.h"

namespace gui {
namespace search {
SelectedPreview::SelectedPreview(QWidget *parent)
    : QWidget(parent),
      layout_(new QHBoxLayout(this)),
      edit_button_(new QPushButton("Modifica", this)),
      fast_edit_button_(new QPushButton("Modifica Rapida", this)),
      delete_button_(new QPushButton("Elimina", this)),
      buttons_(new QWidget(this)),
      displayed_result_(new QWidget(this)) {
  edit_button_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  fast_edit_button_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  delete_button_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

  auto *buttons_layout = new QVBoxLayout(buttons_);
  buttons_layout->setAlignment(Qt::AlignRight);
  buttons_layout->addWidget(edit_button_);
  buttons_layout->addWidget(fast_edit_button_);
  buttons_layout->addStretch();
  buttons_layout->addWidget(delete_button_);

  layout_->addWidget(displayed_result_);
  layout_->addWidget(buttons_);
  buttons_->hide();

  connect(edit_button_, &QAbstractButton::clicked, this, [&]() {
    if (selected_) emit editPressed(selected_);
  });
  connect(fast_edit_button_, &QAbstractButton::clicked, this, [&]() {
    if (selected_) emit fastEditPressed(selected_);
  });
  connect(delete_button_, &QAbstractButton::pressed, this, [&]() {
    if (selected_) emit deletePressed(selected_);
  });
}

void SelectedPreview::display(const media::Media *media) {
  if (displayed_result_) {
    layout_->removeWidget(displayed_result_);
    displayed_result_->deleteLater();
    displayed_result_ = nullptr;
  }
  if (buttons_->isHidden()) buttons_->show();

  if (media != selected_) selected_ = media;
  if (!media) return;

  PreviewVisitor v;
  media->media::Media::accept(v);
  displayed_result_ = v.getWidget();
  layout_->insertWidget(0, displayed_result_);
}

void SelectedPreview::clear() {
  display(nullptr);
  buttons_->hide();
}

}  // namespace search
}  // namespace gui
