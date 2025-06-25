#ifndef PROFILE_H
#define PROFILE_H

#include <QFrame>
#include <QPushButton>
#include <QToolButton>
#include <QWidget>

#include "MainWindow.h"

namespace gui {
class DatabaseSelectionWidget : public QWidget {
  Q_OBJECT

 private:
  MainWindow &main_window_;
  QToolButton *open_db_;
  QToolButton *create_db_;

  const QString tool_style_sheet_;
  QSize button_size_;  // da dinamicizzare? oppure potremmo rendere fissa /
                       // grandezza massima la grandezza della finestra in
                       // questa posizione (poi da gestire transazione da
                       // database aperto a questa schermata eventuale)

  QToolButton *makeToolButton(const QString &name, const QPixmap &image,
                              QWidget *parent);

 public:
  explicit DatabaseSelectionWidget(MainWindow *main_window);

 signals:
  void onPressRecent(size_t);
  void onPressNew(); // ?
  void onPressOpen(); // ?
};
}  // namespace gui
#endif
