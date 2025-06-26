#ifndef GUI_ADVANCED_SEARCH_EBOOK_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_EBOOK_INPUT_WIDGET_H
#include <QCheckBox>
#include "NovelInputWidget.h"
#include "../../Media/Ebook.h"

namespace gui {
namespace advanced_search {
class EbookInputWidget : public NovelInputWidget {
  Q_OBJECT
 private:
 QCheckBox *drm_;

public:
  explicit EbookInputWidget(QWidget *parent = nullptr);
  media::Ebook *getFilter(const media::Media &base) const override;
};
}  // namespace advanced_search
}  // namespace gui
#endif
