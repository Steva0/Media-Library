#include "ProfileButton.h"

ProfileButton::ProfileButton(const QString &profile_name, QWidget *parent) : QPushButton(profile_name, parent) {
 
}

int ProfileButton::heightForWidth(int w) const {
  return w;
}
