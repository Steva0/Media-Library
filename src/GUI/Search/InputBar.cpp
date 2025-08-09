#include "InputBar.h"

namespace gui {
namespace search {
InputBar::InputBar(int timerDurationMillis, QWidget *parent)
    : QLineEdit(parent),
      timer_(new QTimer(this)),
      kTimerDurationMillis_(timerDurationMillis)
{
  timer_->setSingleShot(true);
  timer_->setInterval(kTimerDurationMillis_);
  timer_->start(kTimerDurationMillis_);

  connect(this, &QLineEdit::textEdited, timer_, [this]() { timer_->start(kTimerDurationMillis_); });
  connect(timer_, &QTimer::timeout, this, [this]() { emit timedEdit(text()); });
}
}  // namespace search
}  // namespace gui
