#ifndef PROFILE_H
#define PROFILE_H

#include <QFrame>
#include <QPushButton>
#include <QToolButton>
#include <QWidget>
namespace gui {

class MainWindow;

class DatabaseSelectionWidget : public QWidget {
  Q_OBJECT

 private:
  QToolButton *open_db_;
  QToolButton *create_db_;

  const QString tool_style_sheet_;
  QSize button_size_;

  QToolButton *makeToolButton(const QString &name, const QPixmap &image, QWidget *parent);

 public:
  explicit DatabaseSelectionWidget(QWidget *parent = nullptr);

 signals:
  void onSelectDatabase();
  void onCreateDatabase();
};
}  // namespace gui
#endif
