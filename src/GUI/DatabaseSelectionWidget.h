#ifndef PROFILE_H
#define PROFILE_H

#include <QPushButton>
#include <QToolButton>
#include <QWidget>
#include <QFrame>
#include "MainWindow.h"

namespace gui {
class DatabaseSelectionWidget : public QWidget {
  Q_OBJECT

private:
  MainWindow &main_window_;
  QToolButton *open_other_;
  QToolButton *recently_opened_[3];
  QToolButton *create_new_;
  unsigned int recent_amount_; // grandezza recenty_opened_

  QString tool_style_sheet_;
  QSize button_size_; // da dinamicizzare? oppure potremmo rendere fissa /
                      // grandezza massima la grandezza della finestra in questa
                      // posizione (poi da gestire transazione da database
                      // aperto a questa schermata eventuale)

  QToolButton *makeToolButton(const QString &name, const QPixmap &image,
                              QWidget *parent);
  QFrame *makeVLine(QWidget *parent);


public:
  explicit DatabaseSelectionWidget(MainWindow *main_window);

signals:
  void set_profile(int);
  void change();
};
}
#endif
