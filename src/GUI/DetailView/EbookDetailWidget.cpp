#include "EbookDetailWidget.h"

namespace gui {

EbookDetailWidget::EbookDetailWidget(QWidget* parent) : NovelDetailWidget(parent, false) {
  fileSizeLabel_ = new QLabel("Dimensione File: ", this);
  leftLayout_->addWidget(fileSizeLabel_);

  drmLabel_ = new QLabel("DRM: ", this);
  leftLayout_->addWidget(drmLabel_);
  
  leftLayout_->addWidget(notesLabel_);
  fileSizeLabel_->setWordWrap(true);
  drmLabel_->setWordWrap(true);
}

void EbookDetailWidget::setMedia(const media::Media* media) {
  NovelDetailWidget::setMedia(media);

  const media::Ebook* ebook = dynamic_cast<const media::Ebook*>(media);
  if (!ebook) {
    fileSizeLabel_->setText("Dimensione File: ");
    drmLabel_->setText("DRM: ");
    return;
  }

  qint64 fileSizeBytes = ebook->getFileSizeBytes();
  if (fileSizeBytes > 0) {
    double sizeMB = static_cast<double>(fileSizeBytes) / (1024.0 * 1024.0);
    fileSizeLabel_->setText(QString("Dimensione File: %1 MB").arg(sizeMB, 0, 'f', 2));
  } else {
    fileSizeLabel_->setText("Dimensione File: ");
  }

  drmLabel_->setText(QString("DRM: %1").arg(ebook->hasDrm() ? "Sì" : "No"));
}

void EbookDetailWidget::updateTextFontSize() {
  NovelDetailWidget::updateTextFontSize();  // Chiama la base per gestire le label comuni

  // Applica il font normale alle label aggiuntive
  fileSizeLabel_->setFont(normalLabelFont_);
  drmLabel_->setFont(normalLabelFont_);
}

}  // namespace gui
