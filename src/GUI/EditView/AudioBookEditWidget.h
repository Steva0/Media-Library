#ifndef GUI_MEDIAEDIT_AUDIOBOOKEDITWIDGET_H
#define GUI_MEDIAEDIT_AUDIOBOOKEDITWIDGET_H

#include "NovelEditWidget.h"
#include <QLineEdit>

namespace gui {

class AudioBookEditWidget : public NovelEditWidget {
  Q_OBJECT
 public:
  explicit AudioBookEditWidget(QWidget *parent = nullptr);

  void setMedia(const media::Media* media) override;

private:
  QLineEdit* narrator_input_;
  QLineEdit* streaming_service_input_;

  media::Media* getModifiedMedia() const override;
};

}  // namespace gui

#endif  // GUI_MEDIAEDIT_AUDIOBOOKEDITWIDGET_H
