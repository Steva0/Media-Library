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

 private:
  QSpinBox* episodes_input_;
  QSpinBox* seasons_input_;
  QCheckBox* ended_checkbox_;

  media::Media* getModifiedMedia() const override;
};

}  // namespace gui

#endif  // GUI_MEDIAEDIT_SERIESEDITWIDGET_H
