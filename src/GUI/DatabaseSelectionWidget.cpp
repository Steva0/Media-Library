#include "DatabaseSelectionWidget.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>

namespace gui {
DatabaseSelectionWidget::DatabaseSelectionWidget(MainWindow *main_window)
    : QWidget(main_window),
      main_window_(*main_window),
      tool_style_sheet_("font-size: 20px;"),
      button_size_(128, 128) {

  auto *recent_wrapper = new QFrame(this);
  recent_wrapper->setLayout(new QHBoxLayout);
  recent_wrapper->setFrameStyle(QFrame::NoFrame);
  recent_wrapper->setLineWidth(1);

  open_other_ = makeToolButton("Apri", QPixmap(":/assets/wifi.jpeg"), this);
  create_new_ = makeToolButton("Nuovo", QPixmap(":/assets/matita.jpg"), this);

  for (size_t i = 0; i < 3; ++i) {
    if (main_window_.getRecentFilename(i) != "") {
      // verosimilmente bisognerà troncare il nome
      recently_opened_[i] =
          makeToolButton(main_window_.getRecentFilename(i),
                         QPixmap(":/assets/profilo.png"), recent_wrapper);
      recent_wrapper->layout()->addWidget(recently_opened_[i]);
      recent_wrapper->setMaximumSize(recent_wrapper->minimumSizeHint());
    }
  }

  QFrame *left_line = makeVLine(recent_wrapper);
  QFrame *right_line = makeVLine(recent_wrapper);

  auto *frame_wrapper = new QFrame(this);
  frame_wrapper->setFrameStyle(QFrame::Box);
  frame_wrapper->setLineWidth(2);
  frame_wrapper->setLayout(new QHBoxLayout);
  frame_wrapper->layout()->addWidget(open_other_);

  if (recent_wrapper->layout()->count()) {
    frame_wrapper->layout()->addWidget(left_line);
    frame_wrapper->layout()->addWidget(recent_wrapper);
    frame_wrapper->layout()->addWidget(right_line);
  }

  frame_wrapper->layout()->addWidget(create_new_);
  frame_wrapper->layout()->setContentsMargins(45, 45, 45, 45);
  frame_wrapper->layout()->setSpacing(45);
  frame_wrapper->setMaximumSize(frame_wrapper->minimumSizeHint());

  auto *layout = new QHBoxLayout;
  layout->addWidget(frame_wrapper);

  setLayout(layout);
}

QToolButton *DatabaseSelectionWidget::makeToolButton(const QString &name,
                                                     const QPixmap &image,
                                                     QWidget *parent) {
  auto *new_button = new QToolButton(parent);
  new_button->setText(name);
  new_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  new_button->setIcon(QIcon(image));
  new_button->setIconSize(button_size_);
  new_button->setStyleSheet(tool_style_sheet_);
  return new_button;
}

QFrame *DatabaseSelectionWidget::makeVLine(QWidget *parent) {
  auto *frame = new QFrame(parent);
  frame->setFrameShape(QFrame::VLine);
  frame->setLineWidth(1);
  return frame;
}
}  // namespace gui
