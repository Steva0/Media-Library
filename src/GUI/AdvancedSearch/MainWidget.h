#ifndef GUI_ADVANCED_SEARCH_MAIN_WIDGET_H
#define GUI_ADVANCED_SEARCH_MAIN_WIDGET_H
#include <QWidget>
#include "../AbstractSearchWidget.h"

#include "InputWidget.h"
#include "ResultsWidget.h"
namespace gui {
namespace advanced_search {
class MainWidget : public AbstractSearchWidget {
  Q_OBJECT
 private:
  QPushButton *back_;
  InputWidget *input_;
  ResultsWidget *results_;
  QPushButton *search_;

 public:
  explicit MainWidget(QWidget *parent = nullptr);

 signals:
  void mediaDoubleClicked(const media::Media *media);
  void backRequested();
protected:
  void keyPressEvent(QKeyEvent* event) override;
};
}  // namespace advanced_search
}  // namespace gui

#endif
