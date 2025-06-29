#include "EbookDetailWidget.h"

namespace gui {

EbookDetailWidget::EbookDetailWidget(QWidget* parent) : NovelDetailWidget(parent) {
  fileSizeLabel_ = new QLabel("File Size: ", this);
  leftLayout_->addWidget(fileSizeLabel_);

  drmLabel_ = new QLabel("DRM: ", this);
  leftLayout_->addWidget(drmLabel_);
}

void EbookDetailWidget::setMedia(const media::Media* media) {
  NovelDetailWidget::setMedia(media);

  const media::Ebook* ebook = dynamic_cast<const media::Ebook*>(media);
  if (!ebook) {
    fileSizeLabel_->setText("File Size: ");
    drmLabel_->setText("DRM: ");
    return;
  }

  qint64 fileSizeBytes = ebook->getFileSizeBytes();
  if (fileSizeBytes > 0) {
    double sizeMB = static_cast<double>(fileSizeBytes) / (1024.0 * 1024.0);
    fileSizeLabel_->setText(QString("File Size: %1 MB").arg(sizeMB, 0, 'f', 2));
  } else {
    fileSizeLabel_->setText("File Size: ");
  }

  drmLabel_->setText(QString("DRM: %1").arg(ebook->hasDrm() ? "Yes" : "No"));
}


}  // namespace gui
