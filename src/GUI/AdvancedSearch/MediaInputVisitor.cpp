#include "MediaInputVisitor.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>


namespace gui {
namespace advanced_search {
SubtypeInputWidget *MediaInputVisitor::getWidget() { return widget_; }
void MediaInputVisitor::visit(const media::Album &album) {
  widget_ = new SubtypeInputWidget;
  layout_ = new QGridLayout(widget_);
  layout_->addWidget(new QLabel("Band:", widget_), layout_->rowCount(), 0);
  layout_->addWidget(new QLineEdit(widget_), layout_->rowCount() - 1, 1);
}
void MediaInputVisitor::visit(const media::Movie &) {}
void MediaInputVisitor::visit(const media::Series &) {}
void MediaInputVisitor::visit(const media::Novel &) {}
void MediaInputVisitor::visit(const media::AudioBook &) {}
void MediaInputVisitor::visit(const media::Ebook &) {}
}  // namespace advanced_search
}  // namespace gui
