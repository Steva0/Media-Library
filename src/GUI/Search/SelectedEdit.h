#ifndef GUI_SEARCH_SELECTED_EDIT_H
#define GUI_SEARCH_SELECTED_EDIT_H
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "../../Media/Album.h"
#include "../../Media/AudioBook.h"
#include "../../Media/Ebook.h"
#include "../../Media/Media.h"
#include "../../Media/Movie.h"
#include "../../Media/Novel.h"
#include "../../Media/Series.h"

namespace gui {
namespace search {
class SelectedEdit : public QWidget {
  Q_OBJECT
 private:
  QLabel *type_;
  QLabel *preview_;
  QLineEdit *title_;
  QLineEdit *release_;
  QLineEdit *language_;
  QCheckBox *favourite_;
  QString title_edit_sheet_;

  QPushButton *cancel_;
  QPushButton *confirm_;
  QPushButton *delete_;

  const media::Media *selected_;

 public:
  explicit SelectedEdit(QWidget *parent = nullptr);

 signals:
  void commitChanges(media::Media *new_media, const media::Media *old_media);
  void undoChanges();
  void requestDelete(const media::Media *target);

 public slots:
  void display(const media::Media *);
 private slots:
  void makeMediaAndCommit();
};
}  // namespace search
}  // namespace gui
#endif
