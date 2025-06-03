#ifndef PROFILE_H
#define PROFILE_H

#include <QPushButton>
#include <QToolButton>
// #include "./ProfileButton.h"
#include <QWidget>

class Profile : public QWidget {
  Q_OBJECT

private:
  // QPushButton *buttons_[3];
  QToolButton *buttons_[3];
  // ProfileButton *buttons_[3];

public:
  Profile(QWidget *parent);

signals:
  void set_profile(int);
  void change();
};
#endif
