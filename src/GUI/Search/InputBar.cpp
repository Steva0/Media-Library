#include "InputBar.h"

namespace gui {
namespace search {
const int InputBar::kTimerDuration = 500;
InputBar::InputBar(QWidget *parent) : QLineEdit(parent), timer_(new QTimer(this)) {
  timer_->setSingleShot(true);
  timer_->setInterval(kTimerDuration);
  timer_->start(kTimerDuration);

  connect(this, &QLineEdit::textEdited, timer_, [this]() { timer_->start(kTimerDuration); });
  connect(timer_, &QTimer::timeout, this, [this]() { emit timedEdit(text()); });
}
}  // namespace search
}  // namespace gui
