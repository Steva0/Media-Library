#ifndef GUI_SEARCH_GRID_RESULTS_H
#define GUI_SEARCH_GRID_RESULTS_H

#include <QGridLayout>
#include <QWidget>

#include "../../Media/Media.h"
namespace gui {
namespace search {
class GridResults : public QWidget {
  Q_OBJECT
 private:
  QGridLayout *grid_;
  std::vector<const media::Media *> results_;

 public:
  explicit GridResults(QWidget *parent = nullptr);

 public slots:
  void updateResults(const std::vector<const media::Media *> &results);
};
}  // namespace search
}  // namespace gui

#endif
