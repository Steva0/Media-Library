#include "MainWidget.h"
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
  title_ = new QLabel("**Title**", this);
  title_->setTextFormat(Qt::TextFormat::MarkdownText);

  content_ = new QTextEdit(this);
  content_->setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
  content_->setTextInteractionFlags(Qt::TextInteractionFlag::NoTextInteraction);

  change_ = new QPushButton("Change", this);
  connect(change_, &QPushButton::pressed, this, &MainWidget::change);

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(title_);
  layout->addWidget(content_);
  layout->addWidget(change_);
}
