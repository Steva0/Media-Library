#ifndef GUI_SEARCH_SEARCH_PREVIEW_H
#define GUI_SEARCH_SEARCH_PREVIEW_H
#include <QHBoxLayout>
#include <QPushButton>

#include "../../Media/Media.h"

namespace gui {
namespace search {
class SelectedPreview : public QWidget {
  Q_OBJECT
 private:
  QHBoxLayout *layout_;

  QPushButton *edit_button_;
  QPushButton *fast_edit_button_;
  QPushButton *delete_button_;
  QWidget *buttons_;
  QWidget *displayed_result_;

  const media::Media *selected_;

 public:
  explicit SelectedPreview(QWidget *parent = nullptr);

 signals:
  void deletePressed(const media::Media *);
  void editPressed(const media::Media *);
  void fastEditPressed(const media::Media *);

 public slots:
  void display(const media::Media *);
  void clear();
};
}  // namespace search
}  // namespace gui
#endif
