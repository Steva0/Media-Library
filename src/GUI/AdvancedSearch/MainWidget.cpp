#include "MainWidget.h"

namespace gui {
namespace advanced_search {
MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
  back_ = new QPushButton("BACK", this);
  input_ = new InputWidget(this);
  results_ = new ResultsWidget(this);
  search_ = new QPushButton("SEARCH", this);

  // aggiungere separatore per risultati

  auto *navigation_layout = new QHBoxLayout;
  navigation_layout->addStretch();
  navigation_layout->addWidget(back_);
  navigation_layout->addStretch();
  navigation_layout->addWidget(search_);
  navigation_layout->addStretch();

  auto *input_wrapper = new QWidget(this);
  auto *input_layout = new QVBoxLayout(input_wrapper);
  input_layout->addWidget(input_);
  input_layout->addStretch();
  input_layout->addLayout(navigation_layout);

  input_wrapper->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

  auto *results_wrapper = new QScrollArea(this);
  results_wrapper->setWidget(results_);
  results_wrapper->setWidgetResizable(true);

  auto *layout = new QHBoxLayout(this);
  layout->addWidget(input_wrapper);
  layout->addWidget(results_wrapper);
  
  connect(search_, &QAbstractButton::clicked, this, &MainWidget::performSearch);
  connect(results_, &ResultsWidget::mediaDoubleClicked, this, &MainWidget::mediaDoubleClicked);
}

void MainWidget::performSearch() {
  media::Media *filter = input_->makeFilter();
  emit requestResults(filter);
}

void MainWidget::updateResults(const std::vector<const media::Media *> &new_results) {
  results_->updateResults(new_results);
}
}
}
