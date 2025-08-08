#ifndef GUI_SEARCH_SEARCH_MAIN_H
#define GUI_SEARCH_SEARCH_MAIN_H
#include <QStackedWidget>

#include "../AbstractSearchWidget.h"
#include "GridResults.h"
#include "SearchWidget.h"
#include "SelectedEdit.h"
#include "SelectedPreview.h"

namespace gui {
namespace search {
class SearchMain : public AbstractSearchWidget {
  Q_OBJECT
 private:
  SearchWidget *search_input_;
  GridResults *results_;
  QStackedWidget *selected_;
  SelectedPreview *preview_;
  SelectedEdit *edit_;
  QWidget *placeholder_;

 public:
  explicit SearchMain(QWidget *parent = nullptr);

 private slots:
  void undoEditChanges();
  void fastEditClicked(const media::Media *);
  void clear();

 public slots:
  void hidePreview();
  void showPreview(const media::Media *);

 signals:
  void advancedClicked();
  void mediaDoubleClicked(const media::Media *);
  void requestEdit(const media::Media *);
  void commitEditChanges(const media::Media *new_media, const media::Media *old_media);
  void requestDelete(const media::Media *);
  void addNewMedia();
};
}  // namespace search
}  // namespace gui
#endif
