#ifndef GUI_ADVANCED_SEARCH_AUDIOBOOK_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_AUDIOBOOK_INPUT_WIDGET_H
#include <QComboBox>
#include "NovelInputWidget.h"
#include <QLineEdit>
namespace gui {
namespace advanced_search {
class AudioBookInputWidget : public NovelInputWidget {
  Q_OBJECT
 private:
  QLineEdit *narrator_;
  QComboBox *streaming_service_;

  static const QStringList kStreamingServices;

 public:
  explicit AudioBookInputWidget(QWidget *parent = nullptr);
};
}  // namespace advanced_search
}  // namespace gui
#endif
