#include "SearchWidget.h"

#include <QHBoxLayout>

#include "qsizepolicy.h"

namespace gui {
namespace search {
SearchWidget::SearchWidget(QWidget *parent)
  : QWidget(parent),
    input_(new InputBar(this)),
    advanced_search_(new QPushButton("Avanzata", this)),
    add_new_(new QPushButton("Aggiungi Nuovo", this)) {
  auto *layout = new QHBoxLayout(this);

  input_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  advanced_search_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  add_new_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

  // Imposta la proprietà "verde" solo per il pulsante add_new_
  add_new_->setProperty("verde", true);

  layout->addWidget(advanced_search_);
  layout->addWidget(input_);
  layout->addWidget(add_new_);

  layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

  connect(input_, &InputBar::timedEdit, this, [this]() {
  filter_.setTitle(input_->text().toStdString());
  emit simpleSearch(filter_);
  });
  connect(advanced_search_, &QAbstractButton::clicked, this, &SearchWidget::openAdvancedSearch);
  connect(advanced_search_, &QPushButton::clicked, this, &SearchWidget::advancedClicked);
  connect(add_new_, &QAbstractButton::clicked, this, &SearchWidget::addNewMedia);
}
}  // namespace search
}  // namespace gui
