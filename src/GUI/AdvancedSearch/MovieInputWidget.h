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

  void setFromMedia(const media::Media &) override;
  void makeFilterFor(InputWidget &) const override;

  std::string getActor() const;
  std::string getUniverse() const;
};
}  // namespace advanced_search
}  // namespace gui
#endif
