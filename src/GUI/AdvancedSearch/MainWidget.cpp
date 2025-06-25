#include "MainWidget.h"

namespace gui {
namespace advanced_search {
MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
  back_ = new QPushButton("BACK", this);
  input_ = new InputWidget(this);
  // results_ = new ResultsWidget(this);
  search_ = new QPushButton("SEARCH", this);
}

}
}
