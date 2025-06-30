#ifndef PROFILE_H
#define PROFILE_H

#include <QFrame>
#include <QPushButton>
#include <QToolButton>
#include <QWidget>

// #include "MainWindow.h"
// todocambiare

namespace gui {

class MainWindow;

class DatabaseSelectionWidget : public QWidget {
  Q_OBJECT

 private:
  QToolButton *open_db_;
  QToolButton *create_db_;
  // QString accepted_extensions_;

  const QString tool_style_sheet_;
  QSize button_size_;  // da dinamicizzare? oppure potremmo rendere fissa /
                       // grandezza massima la grandezza della finestra in
                       // questa posizione (poi da gestire transazione da
                       // database aperto a questa schermata eventuale)

  QToolButton *makeToolButton(const QString &name, const QPixmap &image, QWidget *parent);

 public:
  explicit DatabaseSelectionWidget(QWidget *parent = nullptr);

 // private slots:
 //  void createDatabase();
 //  void openDatabase();

 signals:
  void onSelectDatabase(/* const QString & */);
  void onCreateDatabase();
};
}  // namespace gui
#endif
