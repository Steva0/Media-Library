#ifndef GRAPHICS_MAIN_WINDOW_H
#define GRAPHICS_MAIN_WINDOW_H
#include <QFrame>
#include <QMainWindow>
#include <QStatusBar>
#include <memory>

#include "../Memory/Database.h"
#include "SlidingStackedWidget.h"

namespace gui {
class MainWindow : public QMainWindow {
  Q_OBJECT
 private:
  memory::Database &database_;

  SlidingStackedWidget *stacked_widget_;
  QFrame *central_widget_;
  QStatusBar *status_bar_;

  static const QString kConfigFileName;
  static const QString kDatabaseDirectory;
  std::unique_ptr<std::array<QString, 3>> recently_opened_;

  void debug_visitor_advanced_search();

 public:
  explicit MainWindow(memory::Database &database, QWidget *parent = nullptr,
                      Qt::WindowFlags flags = Qt::WindowFlags());

  // ritorna "" se non è presente il file numero `number` nell'array
  // (e.g. se richiedo il terzo file ma ne è presente solamente uno tra quelli
  // recenti) oppure se viene dato un indice troppo alto
  QString getRecentFilename(size_t number) const;
  std::vector<const media::Media*> filter(const media::Media &) const;

 private slots:
  void closeDatabase(bool save) const;
  void openRecent(size_t number) const;
};
}  // namespace gui
#endif
