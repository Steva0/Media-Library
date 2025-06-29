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

  QPushButton *cancel_;
  QPushButton *confirm_;
  QPushButton *delete_;

  const media::Media *selected_;

 public:
  explicit SelectedEdit(QWidget *parent = nullptr);

 signals:
  void commitChanges(media::Media *new_media, const media::Media *old_media);
  void undoChanges();
  void requestDelete(const media::Media *target, int num);

 public slots:
  void display(const media::Media *);
 private slots:
  void makeMediaAndCommit();

 public:
  class MediaTypeProbe : media::IConstMediaVisitor {
    friend class SelectedEdit;

   private:
    QString type_;
    MediaTypeProbe() = default;
    MediaTypeProbe(const MediaTypeProbe &) = default;

   public:
    void visit(const media::Media &media) override;
    void visit(const media::Album &album) override;
    void visit(const media::Movie &movie) override;
    void visit(const media::Series &series) override;
    void visit(const media::Novel &novel) override;
    void visit(const media::AudioBook &audiobook) override;
    void visit(const media::Ebook &ebook) override;
  };
  class MediaTypeClone : media::IConstMediaVisitor {
    friend class SelectedEdit;

   private:
    media::Media *clone_;
    MediaTypeClone() = default;
    MediaTypeClone(const MediaTypeClone &) = default;

   public:
    void visit(const media::Media &media) override;
    void visit(const media::Album &album) override;
    void visit(const media::Movie &movie) override;
    void visit(const media::Series &series) override;
    void visit(const media::Novel &novel) override;
    void visit(const media::AudioBook &audiobook) override;
    void visit(const media::Ebook &ebook) override;
  };
};
}  // namespace search
}  // namespace gui
#endif
