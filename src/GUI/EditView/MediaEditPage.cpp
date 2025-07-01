#include "MediaEditPage.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <typeinfo>

#include "../../Media/Album.h"
#include "../../Media/AudioBook.h"
#include "../../Media/Ebook.h"
#include "../../Media/Media.h"
#include "../../Media/Movie.h"
#include "../../Media/Novel.h"
#include "../../Media/Series.h"

namespace gui {
MediaEditPage::MediaEditPage(QWidget* parent) : QWidget(parent) { setupUi(); }

void MediaEditPage::setupUi() {
  auto* main_layout = new QVBoxLayout(this);

  // Top bar with Back button
  auto* top_bar_layout = new QHBoxLayout();
  auto* back_button = new QPushButton("← Back", this);
  back_button->setFixedSize(80, 30);
  connect(back_button, &QPushButton::clicked, this, &MediaEditPage::onBack);
  top_bar_layout->addWidget(back_button);
  top_bar_layout->addStretch();
  main_layout->addLayout(top_bar_layout);

  // Stacked layout for different editing widgets
  stacked_layout_ = new QStackedLayout();
  main_layout->addLayout(stacked_layout_);

  // Instantiate all edit widgets once
  media_edit_widget_ = new MediaEditWidget(this);
  novel_edit_widget_ = new NovelEditWidget(this);
  audiobook_edit_widget_ = new AudioBookEditWidget(this);
  album_edit_widget_ = new AlbumEditWidget(this);
  series_edit_widget_ = new SeriesEditWidget(this);
  movie_edit_widget_ = new MovieEditWidget(this);
  ebook_edit_widget_ = new EbookEditWidget(this);

  stacked_layout_->addWidget(media_edit_widget_);
  stacked_layout_->addWidget(novel_edit_widget_);
  stacked_layout_->addWidget(audiobook_edit_widget_);
  stacked_layout_->addWidget(album_edit_widget_);
  stacked_layout_->addWidget(series_edit_widget_);
  stacked_layout_->addWidget(movie_edit_widget_);
  stacked_layout_->addWidget(ebook_edit_widget_);

  // Bottom bar with Confirm and Delete buttons
  auto* bottom_bar_layout = new QHBoxLayout();
  auto* confirm_button = new QPushButton("Conferma", this);
  auto* delete_button = new QPushButton("Elimina", this);

  connect(confirm_button, &QPushButton::clicked, this, &MediaEditPage::onConfirm);
  connect(delete_button, &QPushButton::clicked, this, &MediaEditPage::onDelete);

  bottom_bar_layout->addWidget(confirm_button);
  bottom_bar_layout->addStretch();
  bottom_bar_layout->addWidget(delete_button);

  main_layout->addLayout(bottom_bar_layout);
}

void MediaEditPage::setMediaToEdit(const media::Media* media) {
  current_media_ = media;

  // RESET di tutti i widget
  novel_edit_widget_->clearInputFields();
  ebook_edit_widget_->clearInputFields();
  audiobook_edit_widget_->clearInputFields();
  movie_edit_widget_->clearInputFields();
  series_edit_widget_->clearInputFields();
  album_edit_widget_->clearInputFields();
  media_edit_widget_->setMedia(nullptr);

  MediaEditWidget* widget = getWidgetForMedia(media);
  if (!widget) return;

  widget->setMedia(media);
  stacked_layout_->setCurrentWidget(widget);
}


MediaEditWidget* MediaEditPage::getWidgetForMedia(const media::Media* media) const {
  if (!media) return nullptr;

  using namespace media;

  if (dynamic_cast<const AudioBook*>(media)) {
    return audiobook_edit_widget_;
  } else if (dynamic_cast<const Series*>(media)) {
    return series_edit_widget_;
  } else if (dynamic_cast<const Ebook*>(media)) {
    return ebook_edit_widget_;
  } else if (dynamic_cast<const Novel*>(media)) {
    return novel_edit_widget_;
  } else if (dynamic_cast<const Album*>(media)) {
    return album_edit_widget_;
  } else if (dynamic_cast<const Movie*>(media)) {
    return movie_edit_widget_;
  } else if (dynamic_cast<const Media*>(media)) {
    return media_edit_widget_;
  }

  return nullptr;
}

void MediaEditPage::onConfirm() {
  auto* widget = getWidgetForMedia(current_media_);
  if (!widget) return;

  media::Media* new_media = widget->getModifiedMedia();
  if (new_media && new_media->getTitle()!= "" ) {
    emit editConfirmed(new_media, current_media_);
  }
}

void MediaEditPage::onDelete() {
  if (current_media_) {
    emit deleteRequested(current_media_);
  }
}

void MediaEditPage::onBack() { emit backRequested(); }

void MediaEditPage::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Escape) {
    onBack();
    event->accept();
  } else if (event->key() == Qt::Key_Delete) {
    if (current_media_) {
      onDelete();
      event->accept();
    }
  } else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
    onConfirm();
    event->accept();
  } else {
    QWidget::keyPressEvent(event);
  }
}

}  // namespace gui
