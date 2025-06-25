#ifndef GUI_ADVANCED_SEARCH_ALBUM_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_ALBUM_INPUT_WIDGET_H
#include <QLineEdit>

namespace gui {
namespace advanced_search {
class AlbumInputWidget : public QWidget {
  Q_OBJECT
 private:
  QLineEdit *band_name_;
  QLineEdit *band_member_;
  QLineEdit *song_;

public:
  explicit AlbumInputWidget(QWidget *parent = nullptr);
};
}  // namespace advanced_search
}  // namespace gui
#endif
