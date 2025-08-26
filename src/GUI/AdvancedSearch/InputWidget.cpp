#include <QVBoxLayout>
#include <iostream>

#include "AlbumInputWidget.h"
#include "AudioBookInputWidget.h"
#include "EbookInputWidget.h"
#include "InputWidget.h"
#include "MediaInputWidget.h"
#include "MovieInputWidget.h"
#include "NovelInputWidget.h"
#include "SeriesInputWidget.h"

namespace gui {
namespace advanced_search {
InputWidget::InputWidget(QWidget *parent) : QWidget(parent) {
  type_selection_ = new TypeSelector(this);
  media_filter_ = new MediaInputWidget(this);

  layout_ = new QVBoxLayout(this);

  layout_->addWidget(type_selection_);
  layout_->addWidget(media_filter_);
  layout_->addStretch();

  // init
  showTypeInput(0);

  connect(type_selection_, &TypeSelector::selectType, this, &InputWidget::showTypeInput);
}

void InputWidget::showTypeInput(int idx) {
  using Type = memory::Database::Type;

  media_filter_->makeFilterFor(*this); // visitor pattern
  media::Media *old = current_filter_.release();

  layout_->removeWidget(media_filter_);
  media_filter_->deleteLater();
  delete media_filter_;

  switch (idx) {
    case static_cast<int>(Type::Series):
      media_filter_ = new SeriesInputWidget(this);
      break;
    case static_cast<int>(Type::Movie):
      media_filter_ = new MovieInputWidget(this);
      break;
    case static_cast<int>(Type::Album):
      media_filter_ = new AlbumInputWidget(this);
      break;
    case static_cast<int>(Type::Novel):
      media_filter_ = new NovelInputWidget(this);
      break;
    case static_cast<int>(Type::AudioBook):
      media_filter_ = new AudioBookInputWidget(this);
      break;
    case static_cast<int>(Type::Ebook):
      media_filter_ = new EbookInputWidget(this);
      break;
    default:
      media_filter_ = new MediaInputWidget(this);
  }

  media_filter_->setFromMedia(*old);
  delete old;

  layout_->insertWidget(1, media_filter_);
}

const media::Media &InputWidget::getFilter() {
  media_filter_->makeFilterFor(*this);
  return *current_filter_;
}

void InputWidget::makeFilterFrom(const MediaInputWidget &media) {
  current_filter_ = std::make_unique<media::Media>(media.getTitle());
  current_filter_->setFavourite(media.getFavourite());
  current_filter_->setLanguage(media.getLanguage());
  current_filter_->setRelease(media.getRelease());
  for (const auto &genre : media.getGenres()) {
    current_filter_->addGenre(genre);
  }
}
void InputWidget::makeFilterFrom(const AlbumInputWidget &media) {
  current_filter_ = std::make_unique<media::Album>(media.getTitle());
  current_filter_->setFavourite(media.getFavourite());
  current_filter_->setLanguage(media.getLanguage());
  current_filter_->setRelease(media.getRelease());
  for (const auto &genre : media.getGenres()) {
    current_filter_->addGenre(genre);
  }
  media::Album& filter = static_cast<media::Album&>(*current_filter_);
  filter.setBand(media.getBandName());
  filter.addMember(media.getBandMember());
  filter.addSong(media.getSong());
}
void InputWidget::makeFilterFrom(const NovelInputWidget &media) {
  current_filter_ = std::make_unique<media::Novel>(media.getTitle());
  current_filter_->setFavourite(media.getFavourite());
  current_filter_->setLanguage(media.getLanguage());
  current_filter_->setRelease(media.getRelease());
  for (const auto &genre : media.getGenres()) {
    current_filter_->addGenre(genre);
  }
  media::Novel &filter = static_cast<media::Novel&>(*current_filter_);
  filter.setAuthor(media.getAuthor());
  filter.setPublisher(media.getPublisher());
  filter.setSeries(media.getSeries());
  filter.setIsbn(media.getISBN());
}
void InputWidget::makeFilterFrom(const AudioBookInputWidget &media) {
  current_filter_ = std::make_unique<media::AudioBook>(media.getTitle());
  current_filter_->setFavourite(media.getFavourite());
  current_filter_->setLanguage(media.getLanguage());
  current_filter_->setRelease(media.getRelease());
  for (const auto &genre : media.getGenres()) {
    current_filter_->addGenre(genre);
  }
  media::AudioBook &filter = static_cast<media::AudioBook &>(*current_filter_);
  filter.setAuthor(media.getAuthor());
  filter.setPublisher(media.getPublisher());
  filter.setSeries(media.getSeries());
  filter.setIsbn(media.getISBN());
  filter.setNarrator(media.getNarrator());
  filter.setStreamingService(media.getStreamingService());
}
void InputWidget::makeFilterFrom(const EbookInputWidget &media) {
  current_filter_ = std::make_unique<media::Ebook>(media.getTitle());
  current_filter_->setFavourite(media.getFavourite());
  current_filter_->setLanguage(media.getLanguage());
  current_filter_->setRelease(media.getRelease());
  for (const auto &genre : media.getGenres()) {
    current_filter_->addGenre(genre);
  }
  media::Ebook &filter = static_cast<media::Ebook &>(*current_filter_);
  filter.setAuthor(media.getAuthor());
  filter.setPublisher(media.getPublisher());
  filter.setSeries(media.getSeries());
  filter.setIsbn(media.getISBN());
  filter.setDrm(media.getDRM());
}
void InputWidget::makeFilterFrom(const MovieInputWidget &media) {
  current_filter_ = std::make_unique<media::Movie>(media.getTitle());
  current_filter_->setFavourite(media.getFavourite());
  current_filter_->setLanguage(media.getLanguage());
  current_filter_->setRelease(media.getRelease());
  for (const auto &genre : media.getGenres()) {
    current_filter_->addGenre(genre);
  }
  media::Movie &filter = static_cast<media::Movie &>(*current_filter_);
  filter.addActor(media.getActor());
  filter.setUniverse(media.getUniverse());
}
void InputWidget::makeFilterFrom(const SeriesInputWidget &media) {
  current_filter_ = std::make_unique<media::Series>(media.getTitle());
  current_filter_->setFavourite(media.getFavourite());
  current_filter_->setLanguage(media.getLanguage());
  current_filter_->setRelease(media.getRelease());
  for (const auto &genre : media.getGenres()) {
    current_filter_->addGenre(genre);
  }
  media::Series &filter = static_cast<media::Series &>(*current_filter_);
  filter.addActor(media.getActor());
  filter.setUniverse(media.getUniverse());
  filter.setEnded(media.getEnded());
}
}  // namespace advanced_search
}  // namespace gui
