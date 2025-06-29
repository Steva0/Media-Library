#ifndef GUI_SEARCH_SEARCH_WIDGET_H
#define GUI_SEARCH_SEARCH_WIDGET_H
#include <QPushButton>

#include "./InputBar.h"

namespace gui {
namespace search {
class SearchWidget : public QWidget {
  Q_OBJECT
 private:
  InputBar *input_;
  QPushButton *advanced_search_;

 public:
  explicit SearchWidget(QWidget *parent = nullptr);

 signals:
  void advancedClicked();
  void searchByName(const QString &);
  void openAdvancedSearch();
};
}  // namespace search
}  // namespace gui

#endif
