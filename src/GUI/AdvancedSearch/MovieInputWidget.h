#ifndef GUI_ADVANCED_SEARCH_MOVIE_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_MOVIE_INPUT_WIDGET_H
#include <QGridLayout>
#include <QLineEdit>

#include "../../Media/Movie.h"
#include "IMediaInputWidget.h"

namespace gui {
namespace advanced_search {
class MovieInputWidget : public IMediaInputWidget {
  Q_OBJECT
 protected:
  QGridLayout *layout_;

 private:
  QLineEdit *actor_;
  QLineEdit *universe_;

 public:
  explicit MovieInputWidget(QWidget *parent = nullptr);

  media::Movie *getFilter(const media::Media &base) const override;
};
}  // namespace advanced_search
}  // namespace gui
#endif
