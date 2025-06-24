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

  QGridLayout *media_left_layout_;
  QGridLayout *media_right_layout_;

  std::vector<QLineEdit *> genres_edit_vector_;

  // QWidget *newTextEntry(const QString &label);
  // QWidget *newVectorEntry(const QString& label);

 public:
  explicit InputWidget(QWidget *parent);

  // private slots:
  //   void addGenre();
};
}  // namespace advanced_search
}  // namespace gui

#endif
