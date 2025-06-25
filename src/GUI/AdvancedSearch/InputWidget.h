#ifndef GUI_ADVANCED_SEARCH_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_INPUT_WIDGET_H
#include <QLineEdit>
#include <QStackedWidget>

#include "MediaInputWidget.h"
#include "TypeSelector.h"

namespace gui {
namespace advanced_search {
class InputWidget : public QWidget {
  Q_OBJECT
 private:
  // selezione del tipo di media cercato sulla base di enum in MediaContainer
  TypeSelector *type_selection_;

  MediaInputWidget *media_filter_;
  QStackedWidget *type_filter_;

 public:
  explicit InputWidget(QWidget *parent = nullptr);

 private slots:
  void showTypeInput(int);

 signals:
  // void filter(const media::Media *); ??
};
}  // namespace advanced_search
}  // namespace gui

#endif
