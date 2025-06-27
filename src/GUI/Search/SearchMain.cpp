#include "SearchMain.h"

#include "GridResults.h"
#include "SearchWidget.h"
#include "SelectedPreview.h"
#include "../PreviewVisitor.h"

namespace gui {
namespace search {
SearchMain::SearchMain(QWidget *parent)
    : QWidget(parent),
      search_input_(new SearchWidget(this)),
      results_(new GridResults(this)),
      preview_(new SelectedPreview(this)) {
  auto *layout = new QGridLayout(this);

  layout->addWidget(search_input_, 0, 0);
  layout->addWidget(preview_, 0, 1);
  layout->addWidget(results_, 1, 0, 1, 2, Qt::AlignBottom);

  connect(search_input_, &SearchWidget::searchByName, this, &SearchMain::requestByName);
  connect(this, &SearchMain::acceptResults, results_, &GridResults::updateResults);
}
}  // namespace search
}  // namespace gui
