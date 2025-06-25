#ifndef GUI_ADVANCED_SEARCH_MAIN_WIDGET_H
#define GUI_ADVANCED_SEARCH_MAIN_WIDGET_H
#include <QWidget>

#include "InputWidget.h"
#include "ResultsWidget.h"
namespace gui {
namespace advanced_search {
class MainWidget : public QWidget {
  Q_OBJECT
 private:
  QPushButton *back_;
  InputWidget *input_;
  ResultsWidget *results_;
  QPushButton *search_;

 public:
  explicit MainWidget(QWidget *parent = nullptr);

signals:
  void backPressed();
  void searchPressed(const media::Media *);
};
}  // namespace advanced_search
}  // namespace gui

#endif
