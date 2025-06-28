#include "SearchMain.h"
#include <iostream>
#include <QScrollArea>

#include "GridResults.h"
#include "SearchWidget.h"
#include "SelectedPreview.h"
#include "qnamespace.h"
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

  top_layout->addWidget(search_input_, 1);
  top_layout->addWidget(top_separator);
  top_layout->addWidget(preview_, 3);

  top_wrapper->setMaximumHeight(top_wrapper->sizeHint().height());

  results_->setFrameShape(QFrame::Box);
  results_->layout()->setAlignment(Qt::AlignTop | Qt::AlignLeft);

  auto *results_wrapper = new QScrollArea(this);
  results_wrapper->setWidget(results_);
  results_wrapper->setWidgetResizable(true);
  results_wrapper->setAlignment(Qt::AlignTop | Qt::AlignLeft);

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(top_wrapper);
  layout->addWidget(results_wrapper);
        
  connect(search_input_, &SearchWidget::searchByName, this, &SearchMain::searchByName);
  connect(this, &SearchMain::acceptResults, results_, &GridResults::updateResults);

  // Pulsanti di preview (edit/delete)
  connect(preview_, &SelectedPreview::editPressed, this, &SearchMain::requestEdit);
  connect(preview_, &SelectedPreview::deletePressed, this, &SearchMain::requestDelete);

  // Doppio click sui risultati
  connect(results_, &GridResults::mediaDoubleClicked, this, &SearchMain::mediaDoubleClicked);
  connect(search_input_, &SearchWidget::advancedClicked, this, &SearchMain::advancedClicked);
}
}  // namespace search
}  // namespace gui
