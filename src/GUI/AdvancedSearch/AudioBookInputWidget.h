#ifndef GUI_ADVANCED_SEARCH_AUDIOBOOK_INPUT_WIDGET_H
#define GUI_ADVANCED_SEARCH_AUDIOBOOK_INPUT_WIDGET_H
#include <QComboBox>
#include <QLineEdit>

#include "../../Media/AudioBook.h"
#include "NovelInputWidget.h"
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
  media::AudioBook *getFilter(const media::Media &base) const override;
};
}  // namespace advanced_search
}  // namespace gui
#endif
