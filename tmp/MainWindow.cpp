#include "MainWindow.h"
#include "MainWidget.h"
#include "Profile.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  sliding_ = new SlidingStackedWidget(this);

  auto *main_widget = new MainWidget(this);
  auto *profile_widget = new Profile(this);

  sliding_->addWidget(profile_widget);
  sliding_->addWidget(main_widget);

  sliding_->setAnimation(QEasingCurve::Type::OutQuart);

  sliding_->setSpeed(450);

  connect(profile_widget, &Profile::set_profile, this,
          &MainWindow::set_profile);
  
  connect(profile_widget, &Profile::change, [=]() {
    if (sliding_->slideInNext()) {
      main_widget->setEnabled(false);
      profile_widget->setEnabled(false);
    }
  });
  connect(main_widget, &MainWidget::change, [=]() {
    if (sliding_->slideInPrev()) {
      main_widget->setEnabled(false);
      profile_widget->setEnabled(false);
    }
  });
  connect(sliding_, &SlidingStackedWidget::animationFinished, [=]() {
    main_widget->setEnabled(true);
    profile_widget->setEnabled(true);
  });

  setCentralWidget(sliding_);
}

void MainWindow::set_profile(int profile) {
  profile_ = profile;
}
