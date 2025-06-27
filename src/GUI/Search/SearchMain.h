#ifndef GUI_SEARCH_SEARCH_MAIN_H
#define GUI_SEARCH_SEARCH_MAIN_H
#include "GridResults.h"
#include "SearchWidget.h"
#include "SelectedPreview.h"

namespace gui {
namespace search {
class SearchMain : public QWidget {
  Q_OBJECT
 private:
  SearchWidget *search_input_;
  GridResults *results_;
  SelectedPreview *preview_;

 public:
  explicit SearchMain(QWidget *parent = nullptr);

 signals:
  void requestByName(const QString &);
  void acceptResults(const std::vector<const media::Media *> &);
};
}  // namespace search
}  // namespace gui
#endif
