#include "InputWidget.h"

#include <QButtonGroup>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace gui {
namespace advanced_search {
InputWidget::InputWidget(QWidget *parent) : QWidget(parent) {
  // pulsante cerca e pulsante indietro stanno in un altro widget, questo è solo
  // quello che fa riferimento alla selezione dei dati
  type_selection_ = new TypeSelector(this);

  media_filter_ = new MediaInputWidget(this);
  // stacked widget normale (non sliding) per sottotipi indicati da pulsanti sopra
  //

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(type_selection_);
  layout->addWidget(media_filter_);
  layout->addStretch();

  // todo riempire in connect
  // todo aggiungere in modo dinamico valori ad array
  // todo generare media a mo' di visitor in modo che possa essere ottenuto dopo emit signal
}
}  // namespace advanced_search
}  // namespace gui
