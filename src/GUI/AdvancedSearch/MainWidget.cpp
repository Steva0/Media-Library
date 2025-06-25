#include "MainWidget.h"

namespace gui {
namespace advanced_search {
MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
  back_ = new QPushButton("BACK", this);
  input_ = new InputWidget(this);
  // results_ = new ResultsWidget(this);
  search_ = new QPushButton("SEARCH", this);

  // aggiungere separatore per risultati

  auto *navigation_layout = new QHBoxLayout;

  navigation_layout->addStretch();
  navigation_layout->addWidget(back_);
  navigation_layout->addStretch();
  navigation_layout->addWidget(search_);
  navigation_layout->addStretch();

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(input_);
  layout->addStretch();
  layout->addLayout(navigation_layout);
}

}
}
