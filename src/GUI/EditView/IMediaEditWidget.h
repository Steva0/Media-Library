#ifndef GUI_MEDIAEDIT_IMEDIAEDITWIDGET_H
#define GUI_MEDIAEDIT_IMEDIAEDITWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QCheckBox>
#include "../../Media/Media.h"
#include "../../Media/Movie.h"
#include "../../Media/Series.h"
#include "../../Media/Album.h"
#include "../../Media/Novel.h"
#include "../../Media/Ebook.h"
#include "../../Media/AudioBook.h"

namespace gui {

class IMediaEditWidget : public QWidget {
  Q_OBJECT
 public:
  explicit IMediaEditWidget(QWidget* parent = nullptr) : QWidget(parent) {}
  virtual ~IMediaEditWidget() = default;

  virtual void setMedia(const media::Media* media) = 0;
  virtual media::Media* getModifiedMedia() const = 0;  // restituisce nuova copia modificata
};

}  // namespace gui

#endif  // GUI_MEDIAEDIT_IMEDIAEDITWIDGET_H
