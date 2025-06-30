#include "DatabaseSelectionWidget.h"

#include <QFileDialog>
#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>
#include <iostream>

#include "MainWindow.h"

namespace gui {
DatabaseSelectionWidget::DatabaseSelectionWidget(MainWindow *main_window)
    : QWidget(main_window), main_window_(*main_window), tool_style_sheet_("font-size: 20px;"), button_size_(128, 128) {
  open_db_ = makeToolButton("Apri", QPixmap(":/assets/wifi.jpeg"), this);
  create_db_ = makeToolButton("Nuovo", QPixmap(":/assets/matita.jpg"), this);

  auto *layout = new QHBoxLayout(this);
  layout->addStretch();
  layout->addWidget(open_db_);
  layout->addWidget(create_db_);
  layout->addStretch();

  layout->setSpacing(20);

  connect(open_db_, &QAbstractButton::clicked, this, &DatabaseSelectionWidget::openDatabase);
  connect(create_db_, &QAbstractButton::clicked, this, &DatabaseSelectionWidget::createDatabase);
}

void DatabaseSelectionWidget::openDatabase() {
  // todo decidere quale usare
  QString path = QFileDialog::getOpenFileName(nullptr, "Open Database", ".", "XML files (*.xml);;JSON files (*.json)");
  if (path == "") return;  // "cancel"
  emit onSelectDatabase(path);
}

void DatabaseSelectionWidget::createDatabase() {
  QString filter;
  QString path =
      QFileDialog::getSaveFileName(this, "New Database", ".", "XML files(*.xml);;JSON files (*.json)", &filter);
  if (path == "") return;

  if (filter.contains("xml"))
    filter = ".xml";
  else
    filter = ".json";

  if (!path.endsWith(filter)) path += filter;

  emit onSelectDatabase(path);
}

QToolButton *DatabaseSelectionWidget::makeToolButton(const QString &name, const QPixmap &image, QWidget *parent) {
  auto *new_button = new QToolButton(parent);
  new_button->setText(name);
  new_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  new_button->setIcon(QIcon(image));
  new_button->setIconSize(button_size_);
  new_button->setStyleSheet(tool_style_sheet_);
  return new_button;
}
}  // namespace gui
