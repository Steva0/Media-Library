#ifndef GUI_MEDIADETAILS_MEDIADETAILWIDGET_H
#define GUI_MEDIADETAILS_MEDIADETAILWIDGET_H

#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QWidget>

#include "IMediaDetailWidget.h"

namespace media {
class Media;  // forward declaration
}

namespace gui {

class MediaDetailWidget : public IMediaDetailWidget {
  Q_OBJECT

 public:
  explicit MediaDetailWidget(QWidget* parent = nullptr);

  void setMedia(const media::Media* media);

 protected:
  void resizeEvent(QResizeEvent* event) override;
  QVBoxLayout* leftLayout_ = nullptr;
  void updateTextFontSize() override;
  QFont titleLabelFont_;
  QFont normalLabelFont_;
  QLabel* notesLabel_ = nullptr;

 private:
  void updateCoverPixmap();
  void clearFields();

  QWidget* leftWidget_ = nullptr;

  QLabel* titleLabel_ = nullptr;
  QLabel* spacerLabel_ = nullptr;
  QLabel* releaseLabel_ = nullptr;
  QLabel* languageLabel_ = nullptr;
  QLabel* favouriteLabel_ = nullptr;
  QLabel* genresLabel_ = nullptr;

  QLabel* coverLabel_ = nullptr;
  QPixmap coverPixmap_;
};

}  // namespace gui

#endif  // GUI_MEDIADETAILS_MEDIADETAILWIDGET_H
