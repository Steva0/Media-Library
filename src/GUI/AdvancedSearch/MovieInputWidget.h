#ifndef GUI_ADVANCED_SEARCH_MOVIE_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_MOVIE_INPUT_WIDGET_H
#include "IMediaInputWidget.h"
#include "../../Media/Movie.h"
#include <QGridLayout>
#include <QLineEdit>

namespace gui {
namespace advanced_search {
class MovieInputWidget :  public IMediaInputWidget {
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
