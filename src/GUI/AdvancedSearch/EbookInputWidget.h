#ifndef GUI_ADVANCED_SEARCH_EBOOK_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_EBOOK_INPUT_WIDGET_H
#include <QCheckBox>

#include "../../Media/Ebook.h"
#include "NovelInputWidget.h"

namespace gui {
namespace advanced_search {
class EbookInputWidget : public NovelInputWidget {
  Q_OBJECT
 private:
  QCheckBox *drm_;

 public:
  explicit EbookInputWidget(QWidget *parent = nullptr);
  void setFromMedia(const media::Media &) override;
  void makeFilterFor(InputWidget &) const override;

  bool getDRM() const;
};
}  // namespace advanced_search
}  // namespace gui
#endif
