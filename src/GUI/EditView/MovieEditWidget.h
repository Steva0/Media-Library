#ifndef GUI_MEDIAEDIT_MOVIEEDITWIDGET_H
#define GUI_MEDIAEDIT_MOVIEEDITWIDGET_H

#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QVBoxLayout>
#include <vector>

#include "MediaEditWidget.h"

namespace gui {

class MovieEditWidget : public MediaEditWidget {
  Q_OBJECT
 public:
  explicit MovieEditWidget(QWidget* parent = nullptr);

  void setMedia(const media::Media* media) override;
  media::Media* getModifiedMedia() const override;

 private slots:
  void addCastMember();
  void removeCastMember(QLineEdit* cast_line, QPushButton* button);

 protected:
  void clearCast();
  void setCast(const std::vector<std::string>& cast);
  std::vector<std::string> getCast() const;

  QSpinBox* length_input_;
  QLineEdit* universe_input_;

  QWidget* cast_container_;
  QVBoxLayout* cast_layout_;
  QLineEdit* cast_input_;
  QPushButton* add_cast_button_;
  std::vector<QPair<QLineEdit*, QPushButton*>> cast_widgets_;  // coppie lineedit + button
};

}  // namespace gui

#endif  // GUI_MEDIAEDIT_MOVIEEDITWIDGET_H
