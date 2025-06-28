#include "InputWidget.h"

#include <QVBoxLayout>
#include <iostream>

#include "MovieInputWidget.h"
#include "MediaInputWidget.h"
#include "SeriesInputWidget.h"
#include "AlbumInputWidget.h"
#include "NovelInputWidget.h"
#include "EbookInputWidget.h"
#include "AudioBookInputWidget.h"

namespace gui {
namespace advanced_search {
InputWidget::InputWidget(QWidget *parent) : QWidget(parent) {
  // pulsante cerca e pulsante indietro stanno in un altro widget, questo è solo
  // quello che fa riferimento alla selezione dei dati
  type_selection_ = new TypeSelector(this);
  media_filter_ = new MediaInputWidget(this);

  layout_ = new QVBoxLayout(this);

  layout_->addWidget(type_selection_);
  layout_->addWidget(media_filter_);
  layout_->addStretch();

  // init
  showTypeInput(0);

  // todo riempire in connect
  // todo generare media filtro che può essere ottenuto con signal
  connect(type_selection_, &TypeSelector::selectType, this, &InputWidget::showTypeInput);
}

void InputWidget::showTypeInput(int idx) {
  using Type = memory::MediaContainer::Type;

  media::Media *old = makeFilter();
  layout_->removeWidget(media_filter_);
  media_filter_->deleteLater();
  delete media_filter_;

  switch (idx) {
    case static_cast<int>(Type::Series):
      // media_filter_ = new SeriesInputWidget(*old, this);
      media_filter_ = new SeriesInputWidget(this);
      break;
    case static_cast<int>(Type::Movie):
      media_filter_ = new MovieInputWidget(this);
      break;
    case static_cast<int>(Type::Album):
      media_filter_ = new AlbumInputWidget(this);
      break;
    case static_cast<int>(Type::Novel):
      media_filter_ = new NovelInputWidget(this);
      break;
    case static_cast<int>(Type::AudioBook):
      media_filter_ = new AudioBookInputWidget(this);
      break;
    case static_cast<int>(Type::Ebook):
      media_filter_ = new EbookInputWidget(this);
      break;
    default:
      media_filter_ = new MediaInputWidget(this);
  }
  media_filter_->setFromMedia(*old);
  delete old;

  layout_->insertWidget(1, media_filter_);
}

media::Media *InputWidget::makeFilter() { return media_filter_->getFilter(); }
}  // namespace advanced_search
}  // namespace gui
