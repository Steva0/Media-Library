#ifndef GUI_SEARCH_GRID_RESULTS_H
#define GUI_SEARCH_GRID_RESULTS_H

#include <QFrame>
#include <QGridLayout>
#include <vector>

#include "../../Media/Media.h"

namespace gui {
namespace search {

class GridResults : public QFrame {
  Q_OBJECT
 private:
  QGridLayout *grid_;
  std::vector<const media::Media *> results_;

  static const int kResultsPerRow;

  static QWidget *makeResult(const media::Media &);

 public:
  explicit GridResults(QWidget *parent = nullptr);

 public slots:
  void updateResults(const std::vector<const media::Media *> &results);

 signals:
  void mediaDoubleClicked(const media::Media *media);
  void mediaSingleClicked(const media::Media *media);
};

}  // namespace search
}  // namespace gui

#endif
