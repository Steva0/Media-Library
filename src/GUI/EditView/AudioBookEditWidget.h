#ifndef GUI_MEDIAEDIT_AUDIOBOOKEDITWIDGET_H
#define GUI_MEDIAEDIT_AUDIOBOOKEDITWIDGET_H

#include <QLineEdit>

#include "NovelEditWidget.h"

namespace gui {

class AudioBookEditWidget : public NovelEditWidget {
  Q_OBJECT
 public:
  explicit AudioBookEditWidget(QWidget* parent = nullptr, bool min = false);

  void setMedia(const media::Media* media) override;
  media::Media* getModifiedMedia(bool old = true) const override;
  void clearInputFields() override;

 private:
  QLineEdit* narrator_input_;
  QLineEdit* streaming_service_input_;
};

}  // namespace gui

#endif  // GUI_MEDIAEDIT_AUDIOBOOKEDITWIDGET_H
