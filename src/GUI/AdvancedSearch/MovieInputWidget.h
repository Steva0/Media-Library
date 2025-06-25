#ifndef GUI_ADVANCED_SEARCH_MOVIE_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_MOVIE_INPUT_WIDGET_H
#include <QGridLayout>
#include <QLineEdit>

namespace gui {
namespace advanced_search {
class MovieInputWidget : public QWidget {
  Q_OBJECT
 protected:
  QGridLayout *layout_;

 private:
  QLineEdit *actor_;
  QLineEdit *universe_;

 public:
  explicit MovieInputWidget(QWidget *parent = nullptr);
};
}  // namespace advanced_search
}  // namespace gui
#endif
