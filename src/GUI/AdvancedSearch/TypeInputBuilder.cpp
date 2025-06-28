#include "TypeInputBuilder.h"

#include "../../Memory/MediaContainer.h"
#include "AlbumInputWidget.h"
#include "AudioBookInputWidget.h"
#include "EbookInputWidget.h"
#include "GUI/AdvancedSearch/MediaInputWidget.h"
#include "MovieInputWidget.h"
#include "NovelInputWidget.h"
#include "SeriesInputWidget.h"

namespace gui {
namespace advanced_search {
TypeInputBuilder::TypeInputBuilder(QObject *parent) : QObject(parent) {}
void TypeInputBuilder::widgetFromType(int type) {
  using Type = memory::MediaContainer::Type;

  MediaInputWidget *widget;

  switch (type) {
    case static_cast<int>(Type::Album):
      widget = new AlbumInputWidget;
      break;
    case static_cast<int>(Type::Novel):
      widget = new NovelInputWidget;
      break;
    case static_cast<int>(Type::Movie):
      widget = new MovieInputWidget;
      break;
    case static_cast<int>(Type::Ebook):
      widget = new EbookInputWidget;
      break;
    case static_cast<int>(Type::AudioBook):
      widget = new AudioBookInputWidget;
      break;
    case static_cast<int>(Type::Series):
      widget = new SeriesInputWidget;
      break;
    default:
      widget = new MediaInputWidget;
  }

  emit widgetBuilt(widget);
}
}  // namespace advanced_search
}  // namespace gui
