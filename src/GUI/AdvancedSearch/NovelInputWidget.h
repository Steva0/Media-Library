#ifndef GUI_ADVANCED_SEARCH_NOVEL_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_NOVEL_INPUT_WIDGET_H
#include "MediaInputWidget.h"
#include <QLineEdit>

namespace gui {
namespace advanced_search {
class NovelInputWidget : public QWidget {
  Q_OBJECT
 private:
  QLineEdit *author_;
  QLineEdit *publisher_;
  QLineEdit *series_;
  QLineEdit *isbn_;

protected:
  QGridLayout *layout_;

public:
  explicit NovelInputWidget(QWidget *parent);
};
}  // namespace advanced_search
}  // namespace gui
#endif
