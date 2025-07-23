#include "MediaDetailPage.h"

#include <QHBoxLayout>
#include <QSpacerItem>

namespace gui {

MediaDetailPage::MediaDetailPage(QWidget* parent) : QWidget(parent) {
  mainLayout_ = new QVBoxLayout(this);

  // Top bar con bottone back
  auto* topBarLayout = new QHBoxLayout();
  auto* backButton = new QPushButton("Indietro", this);
  backButton->setFixedSize(80, 30);
  connect(backButton, &QPushButton::clicked, this, [this]() {
    emit backRequested();  // segnale specifico per tornare indietro
  });
  topBarLayout->addWidget(backButton);
  topBarLayout->addStretch();

  mainLayout_->addLayout(topBarLayout);

  // Bottom bar con pulsanti Modifica e Elimina
  auto* bottomBarLayout = new QHBoxLayout();

  editButton_ = new QPushButton("Modifica", this);
  removeButton_ = new QPushButton("Elimina", this);

  removeButton_->setProperty("rosso", true);

  bottomBarLayout->addWidget(editButton_, 0, Qt::AlignLeft);
  bottomBarLayout->addStretch();
  bottomBarLayout->addWidget(removeButton_, 0, Qt::AlignRight);

  mainLayout_->addLayout(bottomBarLayout);

  connect(removeButton_, &QPushButton::clicked, [this]() { if (currentMedia_) emit removeMediaRequested(currentMedia_); });
  connect(editButton_, &QPushButton::clicked, this, &MediaDetailPage::onEditClicked);
}

MediaDetailPage::~MediaDetailPage() { clearCurrentDetailWidget(); }

void MediaDetailPage::setMedia(const media::Media* media) {
  clearCurrentDetailWidget();
  currentMedia_ = media;
  if (!media) return;
  createDetailWidgetForMedia(media);
}

void MediaDetailPage::clearCurrentDetailWidget() {
  if (currentDetailWidget_) {
    mainLayout_->removeWidget(currentDetailWidget_);
    currentDetailWidget_->deleteLater();
    currentDetailWidget_ = nullptr;
  }
}

void MediaDetailPage::createDetailWidgetForMedia(const media::Media* media) {
  if (!media) return;

  using namespace media;

  if (dynamic_cast<const Series*>(media)) {
    currentDetailWidget_ = new SeriesDetailWidget(this);
  } else if (dynamic_cast<const Ebook*>(media)) {
    currentDetailWidget_ = new EbookDetailWidget(this);
  } else if (dynamic_cast<const AudioBook*>(media)) {
    currentDetailWidget_ = new AudioBookDetailWidget(this);
  } else if (dynamic_cast<const Movie*>(media)) {
    currentDetailWidget_ = new MovieDetailWidget(this);
  } else if (dynamic_cast<const Novel*>(media)) {
    currentDetailWidget_ = new NovelDetailWidget(this);
  } else if (dynamic_cast<const Album*>(media)) {
    currentDetailWidget_ = new AlbumDetailWidget(this);
  } else {
    // fallback: usa NovelDetailWidget per ora
    currentDetailWidget_ = new MediaDetailWidget(this);
  }

  mainLayout_->insertWidget(1, currentDetailWidget_);
  currentDetailWidget_->setMedia(media);
}

void MediaDetailPage::onEditClicked() { emit enterEditRequested(currentMedia_); }

void MediaDetailPage::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Escape) {
    emit backRequested();
    event->accept();
  } else if (event->key() == Qt::Key_Delete) {
    if (currentMedia_) {
      emit removeMediaRequested(currentMedia_);
      event->accept();
    }
  } else {
    QWidget::keyPressEvent(event);
  }
}

}  // namespace gui
