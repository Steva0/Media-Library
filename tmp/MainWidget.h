#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

class MainWidget : public QWidget {
  Q_OBJECT

private:
  QLabel *title_;
  QTextEdit *content_;
  QPushButton *change_;

public:
  MainWidget(QWidget *parent = nullptr);

signals:
  void change();
};

#endif
