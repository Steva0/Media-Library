#ifndef PROFILE_BUTTON_H
#define PROFILE_BUTTON_H

#include <QPushButton>
#include <QPixmap>

class ProfileButton : public QPushButton {
  Q_OBJECT

public:
  ProfileButton(const QString &profile_name, QWidget *parent = nullptr);
  int heightForWidth(int w) const override;
};

#endif
