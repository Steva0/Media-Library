#include "InputWidget.h"

#include <QVBoxLayout>

#include "AlbumInputWidget.h"
#include "AudioBookInputWidget.h"
#include "EbookInputWidget.h"
#include "IMediaInputWidget.h"
#include "MediaInputWidget.h"
// #include "Memory/MediaContainer.h"
#include "MovieInputWidget.h"
#include "NovelInputWidget.h"
#include "SeriesInputWidget.h"

namespace gui {
namespace advanced_search {
InputWidget::InputWidget(QWidget *parent) : QWidget(parent) {
  // pulsante cerca e pulsante indietro stanno in un altro widget, questo è solo
  // quello che fa riferimento alla selezione dei dati
  auto *novel_widget = new NovelInputWidget(this);
  auto *album_widget = new AlbumInputWidget(this);
  auto *movie_widget = new MovieInputWidget(this);
  auto *ebook_widget = new EbookInputWidget(this);
  auto *audiobook_widget = new AudioBookInputWidget(this);
  auto *series_widget = new SeriesInputWidget(this);

  type_selection_ = new TypeSelector(this);

  media_filter_ = new MediaInputWidget(this);

  type_filter_ = new QStackedWidget(this);

  type_filter_->addWidget(new QWidget(
      this));  // widget vuoto per quando non viene fatta una ricerca su un sottotipo (non strettamente necessario)
  type_filter_->addWidget(novel_widget);  // novel
  type_filter_->addWidget(album_widget);
  type_filter_->addWidget(movie_widget);  // movie
  type_filter_->addWidget(ebook_widget);  // ebook
  type_filter_->addWidget(audiobook_widget);
  type_filter_->addWidget(series_widget);  // series

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(type_selection_);
  layout->addWidget(media_filter_);
  layout->addWidget(type_filter_);

  // init
  showTypeInput(0);

  // todo riempire in connect
  // todo generare media filtro che può essere ottenuto con signal
  connect(type_selection_, &TypeSelector::selectType, type_filter_, &QStackedWidget::setCurrentIndex);
  connect(type_selection_, &TypeSelector::selectType, this, &InputWidget::showTypeInput);
}

void InputWidget::showTypeInput(int idx) {
  type_filter_->setCurrentIndex(idx);
  if (idx == 0) {
    type_filter_->hide();
    return;
  }
  type_filter_->show();
  // workaround per gestire lo scaling in altezza del QStackedWidget
  type_filter_->setFixedHeight(type_filter_->currentWidget()->sizeHint().height());
}

media::Media *InputWidget::makeFilter() {
  if (type_filter_->currentIndex() == static_cast<size_t>(memory::MediaContainer::Type::All))
    return new media::Media(media_filter_->getFilter());

  return static_cast<IMediaInputWidget *>(type_filter_->currentWidget())->getFilter(media_filter_->getFilter());
}
}  // namespace advanced_search
}  // namespace gui
