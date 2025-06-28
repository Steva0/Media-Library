#ifndef GUI_ADVANCED_SEARCH_MOVIE_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_MOVIE_INPUT_WIDGET_H
#include <QGridLayout>
#include <QLineEdit>

#include "../../Media/Movie.h"
#include "MediaInputWidget.h"

namespace gui {
namespace advanced_search {
class MovieInputWidget : public MediaInputWidget {
  Q_OBJECT
 protected:
  QGridLayout *movie_layout_;

 private:
  QLineEdit *actor_;
  QLineEdit *universe_;

 public:
  explicit MovieInputWidget(QWidget *parent = nullptr);

  media::Movie *getFilter() const override;
  void setFromMedia(const media::Media &) override;
};
}  // namespace advanced_search
}  // namespace gui
#endif
