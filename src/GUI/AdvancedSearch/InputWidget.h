#ifndef GUI_ADVANCED_SEARCH_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_INPUT_WIDGET_H
#include <QCheckBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QWidget>

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

  std::vector<QLineEdit *> genres_edit_vector_;

 public:
  explicit InputWidget(QWidget *parent);
};
}  // namespace advanced_search
}  // namespace gui

#endif
