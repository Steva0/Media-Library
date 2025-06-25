#include "InputWidget.h"

#include <QVBoxLayout>

#include "AlbumInputWidget.h"
#include "NovelInputWidget.h"
#include "AudioBookInputWidget.h"
#include "EbookInputWidget.h"
#include "MovieInputWidget.h"
#include "SeriesInputWidget.h"
#include "GUI/AdvancedSearch/MediaInputWidget.h"

namespace gui {
namespace advanced_search {
InputWidget::InputWidget(QWidget *parent) : QWidget(parent) {
  // pulsante cerca e pulsante indietro stanno in un altro widget, questo è solo
  // quello che fa riferimento alla selezione dei dati
  type_selection_ = new TypeSelector(this);

  media_filter_ = new MediaInputWidget(this);

  type_filter_ = new QStackedWidget(this);
  type_filter_->addWidget(
      new QWidget(this));  // widget vuoto per quando non viene fatta una ricerca su un sottotipo
  // bisogna gestire errore grandezza
  // bisognerà chiamare un hide() quando idx = 0
  type_filter_->addWidget(new NovelInputWidget(this)); // novel
  type_filter_->addWidget(new AlbumInputWidget(this));
  type_filter_->addWidget(new MovieInputWidget(this)); // movie
  type_filter_->addWidget(new EbookInputWidget(this)); // ebook
  type_filter_->addWidget(new AudioBookInputWidget(this));
  type_filter_->addWidget(new SeriesInputWidget(this)); // series

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(type_selection_);
  layout->addWidget(media_filter_);
  layout->addWidget(type_filter_);
  layout->addStretch();

  showTypeInput(0);

  // todo riempire in connect
  // todo aggiungere in modo dinamico valori ad array
  // todo generare media a mo' di visitor in modo che possa essere ottenuto dopo emit signal
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
  // type_filter_->setFixedHeight(type_filter_->currentWidget()->sizeHint().height());
  // type_filter_->resize(type_filter_->currentWidget()->width(), type_filter_->currentWidget()->sizeHint().height());
  type_filter_->setFixedHeight(type_filter_->currentWidget()->sizeHint().height());
}
}  // namespace advanced_search
}  // namespace gui
