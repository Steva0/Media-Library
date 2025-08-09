#ifndef GUI_SEARCH_INPUT_BAR_H
#define GUI_SEARCH_INPUT_BAR_H
#include <QLineEdit>
#include <QTimer>
namespace gui {
namespace search {
class InputBar : public QLineEdit {
  Q_OBJECT
 private:
  QTimer *timer_;

  const int kTimerDurationMillis_;

 public:
  explicit InputBar(int timerDurationMillis, QWidget *parent = nullptr);

 signals:
  void timedEdit(const QString &);
};
}  // namespace search
}  // namespace gui
#endif
