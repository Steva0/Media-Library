#include "NovelInputWidget.h"

#include <QGridLayout>
#include <QLabel>

namespace gui {
namespace advanced_search {
NovelInputWidget::NovelInputWidget(QWidget *parent) : QWidget(parent) {
  author_ = new QLineEdit(this);
  publisher_ = new QLineEdit(this);
  series_ = new QLineEdit(this);
  isbn_ = new QLineEdit(this);

  // auto *layout = new QGridLayout(this);
  layout_ = new QGridLayout(this);

  layout_->addWidget(new QLabel("Author:", this), 0, 0);
  layout_->addWidget(author_, 0, 1);
  
  layout_->addWidget(new QLabel("Publisher:", this), 0, 2);
  layout_->addWidget(publisher_, 0, 3);

  layout_->addWidget(new QLabel("Series:", this), 1, 0);
  layout_->addWidget(series_, 1, 1);

  layout_->addWidget(new QLabel("ISBN:", this), 1, 2);
  layout_->addWidget(isbn_, 1, 3);

  // addWidget(new QLabel("Author:", this), author_, true);

  // addWidget(new QLabel("Publisher:", this), publisher_, true);

  // addWidget(new QLabel("Series:", this), series_, true);

  // addWidget(new QLabel("ISBN:", this), isbn_, true);
}
}  // namespace advanced_search
}  // namespace gui
