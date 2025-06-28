#ifndef GRAPHICS_MAIN_WINDOW_H
#define GRAPHICS_MAIN_WINDOW_H
#include <QFrame>
#include <QMainWindow>
#include <QScreen>
#include <QApplication>
#include <QStatusBar>
#include <stack>

#include "../Memory/Database.h"
#include "DetailView/MediaDetailPage.h"
#include "EditView/MediaEditPage.h"
#include "AdvancedSearch/MainWidget.h"
#include "DatabaseSelectionWidget.h"
#include "./Search/SearchMain.h"
#include "SlidingStackedWidget.h"

namespace gui {
class MainWindow : public QMainWindow {
  Q_OBJECT
 private:
  memory::Database &database_;
  std::stack<QWidget*> navigation_stack_;


  DatabaseSelectionWidget *db_selection_widget_;
  advanced_search::MainWidget *advanced_search_widget_;
  search::SearchMain *simple_search_widget_;

  SlidingStackedWidget *stacked_widget_;
  QFrame *central_widget_;
  QStatusBar *status_bar_;

  MediaDetailPage *media_detail_page_;
  MediaEditPage *media_edit_page_;

  // debug
  void debugVisitorNormalSearch();
  void debugTimedEdit();
  void debugNormalSearch();

 public:
  explicit MainWindow(memory::Database &database, QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

 private slots:
  void accessDatabase(const QString &path);
  void closeDatabase(bool save);

  void applyFilterAdvanced(const media::Media *);
  void searchByName(const QString &);

  void onMediaDoubleClicked(const media::Media *media);
  void onBackFromDetail();
  void onRemoveMediaRequested(const media::Media *media);
  void onEnterEditRequested(const media::Media *media);  //Da implementare il cambio di SlideStackedWidget
  void onEditConfirmed(const media::Media *newMedia, const media::Media *oldMedia); //Da collegare Signal di MediaEditPage a questo dentro il costruttore di MainWindow

  void navigateTo(QWidget* next_page);
};
}  // namespace gui
#endif
