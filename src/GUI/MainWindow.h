#ifndef GRAPHICS_MAIN_WINDOW_H
#define GRAPHICS_MAIN_WINDOW_H
#include <QFrame>
#include <QMainWindow>
#include <QStatusBar>

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

  // debug
  void debugVisitorAdvancedSearch();
  void debugShowAdvancedSearchResults();
  void debugShowAdvancedSearchInput();
  void debugShowAdvancedSearchMainWidget();

 public:
  explicit MainWindow(memory::Database &database, QWidget *parent = nullptr,
                      Qt::WindowFlags flags = Qt::WindowFlags());

  std::vector<const media::Media*> filter(const media::Media &) const;

 private slots:
  void accessDatabase(const QString &path) const;
  void closeDatabase(bool save) const;

  // void advancedSearch(const media::Media *);
};
}  // namespace gui
#endif
