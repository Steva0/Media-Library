#ifndef GUI_ADVANCED_SEARCH_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_INPUT_WIDGET_H
#include <QWidget>
#include <QLineEdit>

namespace gui {
namespace advanced_search {
class AdvancedSearchInputWidget : public QWidget {
  Q_OBJECT
 private:
  QWidget *type_selection_;
  QLineEdit *input_text_;  

  
 public:
  explicit AdvancedSearchInputWidget(QWidget *parent);

  private slots:
    void disableSelection(size_t pressed);
};
}  // namespace advanced_search
}  // namespace gui

#endif
