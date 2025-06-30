#ifndef GUI_ADVANCED_SEARCH_NOVEL_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_NOVEL_INPUT_WIDGET_H
#include <QGridLayout>
#include <QLineEdit>

#include "../../Media/Novel.h"
#include "MediaInputWidget.h"

namespace gui {
namespace advanced_search {
class NovelInputWidget : public MediaInputWidget {
  Q_OBJECT
 private:
  QLineEdit *author_;
  QLineEdit *publisher_;
  QLineEdit *series_;
  QLineEdit *isbn_;

 protected:
  QGridLayout *novel_layout_;

 public:
  explicit NovelInputWidget(QWidget *parent = nullptr);

  media::Novel *getFilter() const override;
  void setFromMedia(const media::Media &) override;
};
}  // namespace advanced_search
}  // namespace gui
#endif
