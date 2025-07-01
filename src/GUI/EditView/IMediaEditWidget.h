#ifndef GUI_MEDIAEDIT_IMEDIAEDITWIDGET_H
#define GUI_MEDIAEDIT_IMEDIAEDITWIDGET_H

#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QTextEdit>
#include <QWidget>

#include "../../Media/Album.h"
#include "../../Media/AudioBook.h"
#include "../../Media/Ebook.h"
#include "../../Media/Media.h"
#include "../../Media/Movie.h"
#include "../../Media/Novel.h"
#include "../../Media/Series.h"

namespace gui {

class IMediaEditWidget : public QWidget {
  Q_OBJECT
 public:
  explicit IMediaEditWidget(QWidget* parent = nullptr) : QWidget(parent) {}
  virtual ~IMediaEditWidget() = default;

  virtual void setMedia(const media::Media* media) = 0;
  virtual media::Media* getModifiedMedia(bool old = true) const = 0;  // restituisce nuova copia modificata

protected:
  QLabel* notes_label_;
  QTextEdit* notes_input_;
};

}  // namespace gui

#endif  // GUI_MEDIAEDIT_IMEDIAEDITWIDGET_H
