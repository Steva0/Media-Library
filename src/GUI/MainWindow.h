#ifndef GRAPHICS_MAIN_WINDOW_H
#define GRAPHICS_MAIN_WINDOW_H
#include <QApplication>
#include <QFrame>
#include <QMainWindow>
#include <QScreen>
#include <QStatusBar>
#include <stack>

#include "../Memory/Database.h"
#include "./Search/SearchMain.h"
#include "AdvancedSearch/MainWidget.h"
#include "DatabaseSelectionWidget.h"
#include "DetailView/MediaDetailPage.h"
#include "EditView/MediaEditPage.h"
#include "AddMediaView/AddMediaViewPage.h"
#include "SlidingStackedWidget.h"

namespace gui {
class MainWindow : public QMainWindow {
  Q_OBJECT
 private:
  memory::Database &database_;
  std::stack<QWidget *> navigation_stack_;
  QString last_simple_search_query_;
  QString allowed_filter_;
  bool changes_were_made_;

  QMenu *menu_;
  DatabaseSelectionWidget *db_selection_widget_;
  advanced_search::MainWidget *advanced_search_widget_;
  search::SearchMain *simple_search_widget_;

  SlidingStackedWidget *stacked_widget_;
  QFrame *central_widget_;
  QStatusBar *status_bar_;

  MediaDetailPage *media_detail_page_;
  MediaEditPage *media_edit_page_;
  AddMediaViewPage *add_media_view_page_;

  QWidget *current_search_widget_;
  bool savePopup();

  // debug
  void debugVisitorNormalSearch();
  void debugTimedEdit();
  void debugNormalSearch();

 public:
  explicit MainWindow(memory::Database &database, QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

 private slots:
  void createDatabase();
  void openDatabase();
  void accessDatabase(const QString &path);
  void closeDatabase();
  void saveDatabase();

  void applyFilterAdvanced(const media::Media *);
  void searchByName(const QString &);

  void onMediaDoubleClicked(const media::Media *media);
  void goBack();
  void onRemoveMediaRequested(const media::Media *media);
  void onEnterEditRequested(const media::Media *media);  // Da implementare il cambio di SlideStackedWidget
  void onEditConfirmed(const media::Media *newMedia,
                       const media::Media *oldMedia);  // Da collegare Signal di MediaEditPage a questo dentro il
                                                       // costruttore di MainWindow

  void onAddMedia(media::Media *newMedia);
  void navigateTo(QWidget *next_page);
};
}  // namespace gui
#endif
