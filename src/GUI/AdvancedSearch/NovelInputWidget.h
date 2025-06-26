#ifndef GUI_ADVANCED_SEARCH_NOVEL_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_NOVEL_INPUT_WIDGET_H
#include "IMediaInputWidget.h"
#include "../../Media/Novel.h"
#include <QLineEdit>
#include <QGridLayout>

namespace gui {
namespace advanced_search {
class NovelInputWidget :  public IMediaInputWidget {
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

  media::Novel *getFilter(const media::Media &base) const override;
};
}  // namespace advanced_search
}  // namespace gui
#endif
