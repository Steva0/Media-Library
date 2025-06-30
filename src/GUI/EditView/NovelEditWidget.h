#ifndef GUI_MEDIAEDIT_NOVELEDITWIDGET_H
#define GUI_MEDIAEDIT_NOVELEDITWIDGET_H

#include <QLineEdit>
#include <QSpinBox>

#include "MediaEditWidget.h"

namespace gui {

class NovelEditWidget : public MediaEditWidget {
  Q_OBJECT
 public:
  explicit NovelEditWidget(QWidget* parent = nullptr);

  void setMedia(const media::Media* media) override;

 protected:
  QLabel* pages_label;
  QLineEdit* author_input_;
  QLineEdit* publisher_input_;
  QSpinBox* pages_input_;
  QLineEdit* series_input_;
  QLineEdit* isbn_input_;

  media::Media* getModifiedMedia() const override;
};

}  // namespace gui

#endif  // GUI_MEDIAEDIT_NOVELEDITWIDGET_H
