#include "InputWidget.h"

#include <QVBoxLayout>

#include "MediaInputWidget.h"
#include "Memory/MediaContainer.h"
#include "MediaInputVisitor.h"

namespace gui {
namespace advanced_search {
InputWidget::InputWidget(QWidget *parent) : QWidget(parent), current_filter_(nullptr), filter_input_widget_(nullptr) {
  // pulsante cerca e pulsante indietro stanno in un altro widget, questo è solo
  // quello che fa riferimento alla selezione dei dati
  type_selection_ = new TypeSelector(this);

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(type_selection_);
  layout->addWidget(filter_input_widget_);
  layout->addStretch();

  showTypeInput(0);

  connect(type_selection_, &TypeSelector::selectType, this, &InputWidget::showTypeInput);
}

void InputWidget::showTypeInput(int idx) {
  using Type = memory::MediaContainer::Type;

  media::Media old = *current_filter_;
  delete current_filter_;

  switch (idx) {
    case static_cast<int>(Type::Album):
      current_filter_ = new media::Album(old);
      break;
    case static_cast<int>(Type::AudioBook):
      current_filter_ = new media::AudioBook(media::Novel(old));
      break;
    case static_cast<int>(Type::Ebook):
      current_filter_ = new media::Ebook(media::Novel(old));
      break;
    case static_cast<int>(Type::Movie):
      current_filter_ = new media::Movie(old);
      break;
    case static_cast<int>(Type::Novel):
      current_filter_ = new media::Novel(old);
      break;
    case static_cast<int>(Type::Series):
      current_filter_ = new media::Series(media::Movie(old));
      break;
    default:
      current_filter_ = new media::Media(old);
  }

  MediaInputVisitor v;
  current_filter_->accept(v);

  filter_input_widget_ = v.getWidget();
  filter_input_widget_->setParent(this);
}

const media::Media *InputWidget::makeFilter() {
  return current_filter_;
}
}  // namespace advanced_search
}  // namespace gui
