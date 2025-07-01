#ifndef GUI_MEDIAEDIT_MEDIAEDITWIDGET_H
#define GUI_MEDIAEDIT_MEDIAEDITWIDGET_H

#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QResizeEvent>
#include <QScrollArea>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>
#include <vector>

#include "../../Media/Media.h"
#include "IMediaEditWidget.h"

namespace gui {

class MediaEditWidget : public IMediaEditWidget {
  Q_OBJECT

 public:
  explicit MediaEditWidget(QWidget* parent = nullptr);
  void setMedia(const media::Media* media) override;
  media::Media* getModifiedMedia(bool old = true) const override;

 private slots:
  void addGenre();
  void removeGenre(QLineEdit* genre, QPushButton* removeButton);
  void selectImageFile();

 protected:
  void addNotesSection(QVBoxLayout* layout);
  void resizeEvent(QResizeEvent* event) override;

  const media::Media* old_media_;

  QVBoxLayout* main_layout_;

  QLineEdit* title_input_;
  QSpinBox* release_input_;
  QLineEdit* language_input_;
  QCheckBox* favourite_checkbox_;

  QPushButton* img_select_button_;
  QLabel* img_path_input_;
  QString img_path_;
  QLabel* cover_label_;
  QPixmap cover_pixmap_;

  QLineEdit* genre_input_;
  std::vector<QLineEdit*> genres_;
  QGridLayout* genres_layout_;
  QPushButton* add_genre_button_;

  void clearGenres();
  void setGenres(const std::vector<std::string>& genres);
  std::vector<std::string> getGenres() const;
  void updateCoverPixmap();
};

}  // namespace gui

#endif  // GUI_MEDIAEDIT_MEDIAEDITWIDGET_H
