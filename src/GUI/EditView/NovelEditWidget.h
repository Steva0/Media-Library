#ifndef GUI_MEDIAEDIT_NOVELEDITWIDGET_H
#define GUI_MEDIAEDIT_NOVELEDITWIDGET_H

#include <QLineEdit>
#include <QSpinBox>

#include "MediaEditWidget.h"

namespace gui {

class NovelEditWidget : public MediaEditWidget {
  Q_OBJECT
 public:
  explicit NovelEditWidget(QWidget* parent = nullptr, bool note = true, bool min = false);

  void setMedia(const media::Media* media) override;
  media::Media* getModifiedMedia(bool old = true) const override;
  void clearInputFields() override;

 protected:
  QLabel* pages_label;
  QLineEdit* author_input_;
  QLineEdit* publisher_input_;
  QSpinBox* pages_input_;
  QLineEdit* series_input_;
  QLineEdit* isbn_input_;
};

}  // namespace gui

#endif  // GUI_MEDIAEDIT_NOVELEDITWIDGET_H
