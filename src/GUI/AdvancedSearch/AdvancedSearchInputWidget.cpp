#include "AdvancedSearchInputWidget.h"

#include <QHBoxLayout>
#include <QButtonGroup>
#include <QPushButton>
#include <QVBoxLayout>
#include <limits>

#include "Memory/MediaContainer.h"

namespace gui {
namespace advanced_search {
AdvancedSearchInputWidget::AdvancedSearchInputWidget(QWidget *parent)
    : QWidget(parent) {
  using MediaType = memory::MediaContainer::Type;
  auto media_type_count = static_cast<size_t>(MediaType::TypeCount);
  // pulsante cerca e pulsante indietro stanno in un altro widget, questo è solo
  // quello che fa riferimento alla selezione dei dati

  // un pulsante per enum
  type_selection_ = new QWidget(this);
  auto *type_selection_buttons =  new QButtonGroup(type_selection_);
  auto *type_selection_layout = new QHBoxLayout(type_selection_);

  type_selection_buttons->setExclusive(true);

  type_selection_layout->addStretch();
  for (size_t i = 0; i < media_type_count; ++i) {
    auto *button = new QPushButton(
        QString::fromStdString(
            memory::MediaContainer::typeToString(static_cast<MediaType>(i))),
        this);
    button->setCheckable(true);
    if (i == 0) button->setChecked(true);

    type_selection_buttons->addButton(button);
    type_selection_layout->addWidget(button);
  }

  type_selection_layout->addStretch();

  type_selection_layout->setSpacing(0);

  // accettazione testo in input (meglio sopra?)
  input_text_ = new QLineEdit(this);
  
  // campi media

  // stacked widget normale (non sliding) per sottotipi indicati da pulsanti sopra
 
  auto *layout = new QVBoxLayout(this);
  layout->addWidget(type_selection_);
  layout->addWidget(input_text_);
  layout->addStretch();
}

void AdvancedSearchInputWidget::disableSelection(size_t pressed) {
  for (size_t i = 0;
       i < static_cast<size_t>(memory::MediaContainer::Type::TypeCount); ++i) {
    if (i != pressed)
      static_cast<QPushButton *>(type_selection_->layout()->itemAt(i)->widget())
          ->setChecked(false);
  }
}
}  // namespace advanced_search
}  // namespace gui
