#ifndef GUI_ADVANCED_SEARCH_ALBUM_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_ALBUM_INPUT_WIDGET_H
#include "IMediaInputWidget.h"
#include "../../Media/Album.h"
#include <QLineEdit>

namespace gui {
namespace advanced_search {
class AlbumInputWidget : public IMediaInputWidget {
  Q_OBJECT
 private:
  QLineEdit *band_name_;
  QLineEdit *band_member_;
  QLineEdit *song_;

public:
  explicit AlbumInputWidget(QWidget *parent = nullptr);

  media::Album *getFilter(const media::Media &base) const override;
};
}  // namespace advanced_search
}  // namespace gui
#endif
