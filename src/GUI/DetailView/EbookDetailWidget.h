#ifndef GUI_MEDIADETAILS_EBOOKDETAILWIDGET_H
#define GUI_MEDIADETAILS_EBOOKDETAILWIDGET_H

#include <QLabel>

#include "../../Media/Ebook.h"
#include "NovelDetailWidget.h"

namespace gui {

class EbookDetailWidget : public NovelDetailWidget {
  Q_OBJECT
 public:
  explicit EbookDetailWidget(QWidget* parent = nullptr);

  void setMedia(const media::Media* media) override;
  void updateTextFontSize() override;

 private:
  QLabel* fileSizeLabel_;
  QLabel* drmLabel_;
};

}  // namespace gui

#endif  // GUI_MEDIADETAILS_EBOOKDETAILWIDGET_H
