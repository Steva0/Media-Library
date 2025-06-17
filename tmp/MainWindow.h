#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "./SlidingStackedWidget/slidingstackedwidget.h"
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>

class MainWindow : public QMainWindow {
  Q_OBJECT
private:
  SlidingStackedWidget *sliding_;
  int profile_;

public:
  MainWindow(QWidget *parent = nullptr);

private slots:
  void set_profile(int);
};

#endif
