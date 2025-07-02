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

  std::shared_ptr<media::Media> filter_;

 public:
  explicit MainWidget(QWidget *parent = nullptr);

 signals:
  void mediaDoubleClicked(const media::Media *media);
  // void requestResults(const media::Media &filter);
  void backRequested();
  // void updateResults(const std::vector<const media::Media *> &new_results);
protected:
  void keyPressEvent(QKeyEvent* event) override;
};
}  // namespace advanced_search
}  // namespace gui

#endif
