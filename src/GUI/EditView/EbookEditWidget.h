#ifndef GUI_MEDIAEDIT_EbookEDITWIDGET_H
#define GUI_MEDIAEDIT_EbookEDITWIDGET_H

#include <QCheckBox>
#include <QSpinBox>

#include "NovelEditWidget.h"

namespace gui {

class EbookEditWidget : public NovelEditWidget {
  Q_OBJECT
 public:
  explicit EbookEditWidget(QWidget* parent = nullptr);

  void setMedia(const media::Media* media) override;

 private:
  QSpinBox* file_size_input_;
  QCheckBox* drm_checkbox_;

  media::Media* getModifiedMedia() const override;
};

}  // namespace gui

#endif  // GUI_MEDIAEDIT_EbookEDITWIDGET_H
