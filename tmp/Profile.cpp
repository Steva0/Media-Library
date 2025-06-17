#include "Profile.h"
#include "qabstractbutton.h"
#include "qnamespace.h"
// #include "ProfileButton.h"
#include <QPushButton>
#include <QHBoxLayout>

Profile::Profile(QWidget *parent) : QWidget(parent) {
  for (int i = 0; i < 3; ++i) {
    // buttons_[i] = new QPushButton(QString("Profile ").append(QString::number(i)), this);
    buttons_[i] = new QToolButton(this);
    buttons_[i]->setText(QString("Profile ").append(QString::number(i)));
    buttons_[i]->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  }

  QPixmap wifi_img(":/assets/wifi.jpeg");
  QPixmap pencil_img(":/assets/matita.jpg");
  QPixmap profile_img(":/assets/profilo.png");

  QSize tmp_size(256, 256);

  buttons_[0]->setIcon(QIcon(wifi_img));
  // buttons_[0]->setIconSize(wifi_img.rect().size());
  buttons_[0]->setIconSize(tmp_size);

  buttons_[1]->setIcon(QIcon(pencil_img));
  buttons_[1]->setIconSize(tmp_size);

  buttons_[2]->setIcon(QIcon(profile_img));
  buttons_[2]->setIconSize(tmp_size);

  // buttons_[0]->setIcon(i1);
  // // buttons_[0]->setIconSize(b1.rect().size());
  // buttons_[1]->setIcon(QIcon(QPixmap("assets/matita.jpg")));
  // buttons_[2]->setIcon(QIcon(QPixmap("assets/profilo.png")));

  // buttons_[0]->setFixedSize(100, 100);
  // buttons_[1]->setFixedSize(100, 100);
  // buttons_[2]->setFixedSize(100, 100);

  // buttons_[0] = new ProfileButton("Profile 1", this);
  // buttons_[1] = new ProfileButton("Profile 2", this);
  // buttons_[2] = new ProfileButton("Profile 3", this);

  auto *layout = new QHBoxLayout(this);
  auto *wrapper = new QHBoxLayout(this);
  layout->addLayout(wrapper);
  // layout->addWidget(buttons_[0]);
  // layout->addWidget(buttons_[1]);
  // layout->addWidget(buttons_[2]);
  // layout->setContentsMargins(45, 45, 45, 45);
  // layout->setSpacing(45);
  wrapper->addWidget(buttons_[0]);
  wrapper->addWidget(buttons_[1]);
  wrapper->addWidget(buttons_[2]);
  wrapper->setContentsMargins(45, 45, 45, 45);
  wrapper->setSpacing(45);

  connect(buttons_[0], &QAbstractButton::pressed, this, [&]() { emit set_profile(0); });
  connect(buttons_[1], &QAbstractButton::pressed, this, [&]() { emit set_profile(1); });
  connect(buttons_[2], &QAbstractButton::pressed, this, [&]() { emit set_profile(2); });
  connect(buttons_[0], &QAbstractButton::pressed, this, &Profile::change);
  connect(buttons_[1], &QAbstractButton::pressed, this, &Profile::change);
  connect(buttons_[2], &QAbstractButton::pressed, this, &Profile::change);
}
