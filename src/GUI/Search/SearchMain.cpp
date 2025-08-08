#include <QScrollArea>

#include "GridResults.h"
#include "SearchMain.h"
#include "SearchWidget.h"
#include "SelectedPreview.h"
#include "qnamespace.h"
#include "qsizepolicy.h"

namespace gui {
namespace search {
SearchMain::SearchMain(QWidget *parent)
    : AbstractSearchWidget(parent),
      search_input_(new SearchWidget(this)),
      results_(new GridResults(this)),
      selected_(new QStackedWidget(this)),
      preview_(new SelectedPreview(this)),
      edit_(new SelectedEdit(this)) {
  search_input_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  results_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  selected_->addWidget(edit_);
  selected_->addWidget(preview_);
  selected_->setCurrentWidget(preview_);

  auto *top_wrapper = new QFrame(this);
  top_wrapper->setFrameShape(QFrame::Box);
  auto *top_layout = new QHBoxLayout(top_wrapper);

  auto *top_separator = new QFrame(this);
  top_separator->setFrameShape(QFrame::VLine);
  top_separator->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

  search_input_->layout()->setAlignment(Qt::AlignTop);

  top_layout->addWidget(search_input_, 1);
  top_layout->addWidget(top_separator);
  top_layout->addWidget(selected_, 3);

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

  connect(search_input_, &SearchWidget::simpleSearch, this, &SearchMain::requestResults);
  connect(this, &SearchMain::updateResults, results_, &GridResults::updateResults);

  // Pulsanti di preview (edit/delete)
  connect(preview_, &SelectedPreview::editPressed, this, &SearchMain::requestEdit);
  connect(preview_, &SelectedPreview::deletePressed, this, &SearchMain::requestDelete);
  connect(preview_, &SelectedPreview::deletePressed, this, &SearchMain::hidePreview);
  connect(preview_, &SelectedPreview::fastEditPressed, this, &SearchMain::fastEditClicked);

  connect(edit_, &SelectedEdit::commitChanges, this, &SearchMain::commitEditChanges);
  connect(edit_, &SelectedEdit::undoChanges, this, &SearchMain::undoEditChanges);
  connect(edit_, &SelectedEdit::requestDelete, this, &SearchMain::requestDelete);
  connect(edit_, &SelectedEdit::requestDelete, this, &SearchMain::hidePreview);

  // click sui risultati
  connect(results_, &GridResults::mediaDoubleClicked, this, &SearchMain::mediaDoubleClicked);
  connect(results_, &GridResults::mediaSingleClicked, this, &SearchMain::showPreview);
  connect(search_input_, &SearchWidget::advancedClicked, this, &SearchMain::advancedClicked);
  connect(search_input_, &SearchWidget::advancedClicked, this, &SearchMain::clear);

  connect(search_input_, &SearchWidget::addNewMedia, this, &SearchMain::addNewMedia);
}

void SearchMain::undoEditChanges() {
  edit_->display(nullptr);
  selected_->setCurrentWidget(preview_);
}

void SearchMain::fastEditClicked(const media::Media *media) {
  edit_->display(media);
  selected_->setCurrentWidget(edit_);
}

void SearchMain::showPreview(const media::Media *media) {
  preview_->display(media);
  selected_->setCurrentWidget(preview_);
}

void SearchMain::hidePreview() {
  selected_->setCurrentWidget(preview_);
  preview_->clear();
}

void SearchMain::clear() {
  preview_->clear();  // svuota la preview
}
}  // namespace search
}  // namespace gui
