#ifndef GUI_ADVANCED_SEARCH_EBOOK_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_EBOOK_INPUT_WIDGET_H
#include <QCheckBox>
#include "NovelInputWidget.h"

namespace gui {
namespace advanced_search {
class EbookInputWidget : public NovelInputWidget {
  Q_OBJECT
 private:
 QCheckBox *drm_;

public:
  explicit EbookInputWidget(QWidget *parent = nullptr);
};
}  // namespace advanced_search
}  // namespace gui
#endif
