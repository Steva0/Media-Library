#include "DatabaseSelectionWidget.h"
#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>

namespace gui {
DatabaseSelectionWidget::DatabaseSelectionWidget(QWidget *parent)
    : QWidget(parent), tool_style_sheet_("font-size: 20px;"),
      button_size_(128, 128) {

  // preprocessing...

  //
  QFrame *recent_wrapper = new QFrame(this);
  recent_wrapper->setLayout(new QHBoxLayout);
  recent_wrapper->setFrameStyle(QFrame::NoFrame);
  recent_wrapper->setLineWidth(1);

  open_other_ = makeToolButton("Apri", QPixmap(":/assets/wifi.jpeg"));
  // placeholder
  recently_opened_[0] =
      makeToolButton("Database 1", QPixmap(":/assets/profilo.png"));
  recently_opened_[1] =
      makeToolButton("Database 2", QPixmap(":/assets/profilo.png"));
  recently_opened_[2] =
      makeToolButton("Database 3", QPixmap(":/assets/profilo.png"));
  //
  create_new_ = makeToolButton("Nuovo", QPixmap(":/assets/matita.jpg"));

  recent_wrapper->layout()->addWidget(recently_opened_[0]);
  recent_wrapper->layout()->addWidget(recently_opened_[1]);
  recent_wrapper->layout()->addWidget(recently_opened_[2]);
  recent_wrapper->setMaximumSize(recent_wrapper->minimumSizeHint());

  QFrame *left_line = makeVLine();
  QFrame *right_line = makeVLine();

  auto *frame_wrapper = new QFrame(this);
  frame_wrapper->setFrameStyle(QFrame::Box);
  frame_wrapper->setLineWidth(2);
  frame_wrapper->setLayout(new QHBoxLayout);
  frame_wrapper->layout()->addWidget(open_other_);
  frame_wrapper->layout()->addWidget(left_line);
  frame_wrapper->layout()->addWidget(recent_wrapper);
  frame_wrapper->layout()->addWidget(right_line);
  frame_wrapper->layout()->addWidget(create_new_);
  frame_wrapper->layout()->setContentsMargins(45, 45, 45, 45);
  frame_wrapper->layout()->setSpacing(45);
  frame_wrapper->setMaximumSize(frame_wrapper->minimumSizeHint());

  auto *layout = new QHBoxLayout;
  layout->addWidget(frame_wrapper);

  setLayout(layout);
}

QToolButton *DatabaseSelectionWidget::makeToolButton(const QString &name,
                                                       const QPixmap &image) {
  QToolButton *new_button = new QToolButton(this);
  new_button->setText(name);
  new_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  new_button->setIcon(QIcon(image));
  new_button->setIconSize(button_size_);
  new_button->setStyleSheet(tool_style_sheet_);
  return new_button;
}

QFrame *DatabaseSelectionWidget::makeVLine() {
    QFrame *frame = new QFrame(this);
    frame->setFrameShape(QFrame::VLine);
    frame->setLineWidth(1);
    return frame;
}
}
