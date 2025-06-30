#ifndef GUI_SEARCH_SEARCH_WIDGET_H
#define GUI_SEARCH_SEARCH_WIDGET_H
#include <QPushButton>
#include "../../Media/Media.h"

#include "./InputBar.h"

namespace gui {
namespace search {
class SearchWidget : public QWidget {
  Q_OBJECT
 private:
  InputBar *input_;
  QPushButton *advanced_search_;
  QPushButton *add_new_;
  media::Media filter_;

 public:
  explicit SearchWidget(QWidget *parent = nullptr);

 signals:
  void advancedClicked();
  void simpleSearch(const media::Media &);
  void openAdvancedSearch();
  void addNewMedia();
};
}  // namespace search
}  // namespace gui

#endif
