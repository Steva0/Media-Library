#ifndef GUI_ADVANCED_SEARCH_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_INPUT_WIDGET_H
#include <QLineEdit>
#include <QStackedWidget>

#include "IMediaInputWidget.h"
#include "MediaInputWidget.h"
#include "TypeSelector.h"

namespace gui {
namespace advanced_search {
class InputWidget : public QWidget {
  Q_OBJECT
 private:
  media::Media *current_filter_;
  // selezione del tipo di media cercato sulla base di enum in MediaContainer
  TypeSelector *type_selection_;

  IMediaInputWidget *filter_input_widget_;

 public:
  explicit InputWidget(QWidget *parent = nullptr);

  const media::Media *makeFilter();

 private slots:
  void showTypeInput(int);

 signals:
  void performSearch(const media::Media *filter);
};
}  // namespace advanced_search
}  // namespace gui

#endif
