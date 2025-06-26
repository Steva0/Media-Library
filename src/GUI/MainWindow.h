#ifndef GRAPHICS_MAIN_WINDOW_H
#define GRAPHICS_MAIN_WINDOW_H
#include <QFrame>
#include <QMainWindow>
#include <QStatusBar>

#include "../Memory/Database.h"
#include "SlidingStackedWidget.h"
#include "DatabaseSelectionWidget.h"
#include "AdvancedSearch/MainWidget.h"

namespace gui {
class MainWindow : public QMainWindow {
  Q_OBJECT
 private:
  memory::Database &database_;

  DatabaseSelectionWidget *db_selection_widget_;
  advanced_search::MainWidget *advanced_search_widget_;

  SlidingStackedWidget *stacked_widget_;
  QFrame *central_widget_;
  QStatusBar *status_bar_;

  // debug
  void debugVisitorAdvancedSearch();
  void debugShowAdvancedSearchResults();
  void debugShowAdvancedSearchInput();
  void debugShowAdvancedSearchMainWidget();

 public:
  explicit MainWindow(memory::Database &database, QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

 private slots:
  void accessDatabase(const QString &path);
  void closeDatabase(bool save);

  void applyFilterAdvanced(const media::Media *);
};
}  // namespace gui
#endif
