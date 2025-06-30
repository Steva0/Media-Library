#ifndef GUI_MEDIAEDIT_SERIESEDITWIDGET_H
#define GUI_MEDIAEDIT_SERIESEDITWIDGET_H

#include <QCheckBox>
#include <QSpinBox>

#include "MovieEditWidget.h"

namespace gui {

class SeriesEditWidget : public MovieEditWidget {
  Q_OBJECT
 public:
  explicit SeriesEditWidget(QWidget* parent = nullptr);

  void setMedia(const media::Media* media) override;
  media::Media* getModifiedMedia(bool old = true) const override;

 private:
  QSpinBox* episodes_input_;
  QSpinBox* seasons_input_;
  QCheckBox* ended_checkbox_;
};

}  // namespace gui

#endif  // GUI_MEDIAEDIT_SERIESEDITWIDGET_H
