#include "DatabaseSelectionWidget.h"

#include <QFileDialog>
#include <QFrame>
#include <QHBoxLayout>
#include <QPushButton>


namespace gui {
DatabaseSelectionWidget::DatabaseSelectionWidget(QWidget *parent)
    : QWidget(parent),
      tool_style_sheet_("font-size: 20px;"),
      button_size_(128, 128) {
  open_db_ = makeToolButton("Apri", QPixmap(":/assets/wifi.jpeg"), this);
  create_db_ = makeToolButton("Nuovo", QPixmap(":/assets/matita.jpg"), this);

  auto *layout = new QHBoxLayout(this);
  layout->addStretch();
  layout->addWidget(open_db_);
  layout->addWidget(create_db_);
  layout->addStretch();

  layout->setSpacing(20);

  // connect(open_db_, &QAbstractButton::clicked, this, &DatabaseSelectionWidget::openDatabase);
  // connect(create_db_, &QAbstractButton::clicked, this, &DatabaseSelectionWidget::createDatabase);
  connect(open_db_, &QAbstractButton::clicked, this, &DatabaseSelectionWidget::onSelectDatabase);
  connect(create_db_, &QAbstractButton::clicked, this, &DatabaseSelectionWidget::onCreateDatabase);
}

// void DatabaseSelectionWidget::openDatabase() {
//   // todo decidere quale usare
//   QString path = QFileDialog::getOpenFileName(nullptr, "Open Database", ".", accepted_extensions_);
//   if (path == "") return;  // "cancel"
//   emit onSelectDatabase(path);
// }

// void DatabaseSelectionWidget::createDatabase() {
//   QString filter;
//   QString path = QFileDialog::getSaveFileName(this, "New Database", ".", accepted_extensions_, &filter);
//   if (path == "") return;

//   if (filter.contains("xml"))
//     filter = ".xml";
//   else
//     filter = ".json";

//   if (!path.endsWith(filter)) path += filter;

//   emit onSelectDatabase(path);
// }

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
