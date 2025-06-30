#ifndef GUI_ADVANCED_SEARCH_ALBUM_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_ALBUM_INPUT_WIDGET_H
#include <QLineEdit>

#include "../../Media/Album.h"
#include "MediaInputWidget.h"

namespace gui {
namespace advanced_search {
class AlbumInputWidget : public MediaInputWidget {
  Q_OBJECT
 protected:
  QGridLayout *album_layout_;

 private:
  QLineEdit *band_name_;
  QLineEdit *band_member_;
  QLineEdit *song_;

 public:
  explicit AlbumInputWidget(QWidget *parent = nullptr);

  media::Album *getFilter() const override;
  void setFromMedia(const media::Media &) override;
};
}  // namespace advanced_search
}  // namespace gui
#endif
