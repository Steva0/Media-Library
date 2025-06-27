#include "SearchMain.h"
#include <iostream>

#include "GridResults.h"
#include "SearchWidget.h"
#include "SelectedPreview.h"
#include "qsizepolicy.h"

namespace gui {
namespace search {
SearchMain::SearchMain(QWidget *parent)
    : QWidget(parent),
      search_input_(new SearchWidget(this)),
      results_(new GridResults(this)),
      preview_(new SelectedPreview(this)) {
  search_input_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  results_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  preview_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  
  auto *top_wrapper = new QFrame(this);
  top_wrapper->setFrameShape(QFrame::Box);
  auto *top_layout = new QHBoxLayout(top_wrapper);

  auto *top_separator = new QFrame(this);
  top_separator->setFrameShape(QFrame::VLine);
  top_separator->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

  search_input_->layout()->setAlignment(Qt::AlignTop);

  top_layout->addWidget(search_input_);
  top_layout->addWidget(top_separator);
  top_layout->addWidget(preview_);

  top_wrapper->setMaximumHeight(top_wrapper->sizeHint().height());

  results_->setFrameShape(QFrame::Box);

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(top_wrapper);
  layout->addWidget(results_);

  connect(search_input_, &SearchWidget::searchByName, this, &SearchMain::searchByName);
  connect(this, &SearchMain::acceptResults, results_, &GridResults::updateResults);
  connect(preview_, &SelectedPreview::editPressed, this, &SearchMain::requestEdit);
  connect(preview_, &SelectedPreview::deletePressed, this, &SearchMain::requestDelete);
  connect(search_input_, &SearchWidget::searchByName, this, &SearchMain::searchByName);
}
}  // namespace search
}  // namespace gui
