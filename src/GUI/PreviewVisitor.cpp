#include "./PreviewVisitor.h"

#include <QLabel>
#include <limits>

#include "../Media/Album.h"
#include "../Media/AudioBook.h"
#include "../Media/Ebook.h"
#include "../Media/Media.h"
#include "../Media/Movie.h"
#include "../Media/Novel.h"
#include "../Media/Series.h"

namespace gui {
QWidget *PreviewVisitor::getResult() const { return result_; }
void PreviewVisitor::visit(const media::Media &media) {
  // result_ = new QFrame;
  result_ = new QWidget;
  // result_->setFrameShape(QFrame::Box);
  // result_->setLineWidth(1);

  auto *layout = new QHBoxLayout(result_);
  data_ = new QGridLayout;
  data_->setAlignment(Qt::AlignTop);

  auto *preview = new QLabel(result_);
  // preview->setPixmap(QPixmap(QString::fromStdString(media.getImgPath())).scaled(128, 128));
  preview->setPixmap(QPixmap(QString::fromStdString(":/assets/wifi.jpeg")).scaled(128, 128));

  data_->addWidget(new QLabel(type_), 0, 0);
  if (media.isFavourite()) data_->addWidget(new QLabel("Favourite"));

  addRow("Title:", media.getTitle());
  addRow("Release:", media.getRelease());
  addRow("Language:", media.getLanguage());

  layout->addWidget(preview);
  layout->addLayout(data_);
  layout->addStretch();
}

void PreviewVisitor::visit(const media::Album &album) {
  type_ = "ALBUM";
  visit(static_cast<const media::Media &>(album));
  addRow("Band:", album.getBand());
  addRowVector("Members:", album.getBandMembers());
  addRowVector("Songs:", album.getSongs());
}

void PreviewVisitor::visit(const media::Movie &movie) {
  type_ = "MOVIE ";
  visit(static_cast<const media::Media &>(movie));
  addRow("Duration:", movie.getLength());
  addRow("Universe:", movie.getUniverse());
  addRowVector("Cast:", movie.getCast());
}

void PreviewVisitor::visit(const media::Series &series) {
  type_ = "SERIES ";
  visit(static_cast<const media::Media &>(series));
  addRow("Seasons:", series.getSeasons());
  addRow("Episodes:", series.getEpisodes());
  if (series.hasEnded()) {
    data_->addWidget(new QLabel("Ended", result_), data_->rowCount(), 0);
  }
}

void PreviewVisitor::visit(const media::Novel &novel) {
  type_ = "NOVEL ";
  visit(static_cast<const media::Media &>(novel));
  addRow("Author:", novel.getAuthor());
  addRow("Publisher:", novel.getPublisher());
  addRow("Series:", novel.getSeries());
  addRow("Pages:", novel.getPages());
  addRow("ISBN:", novel.getIsbn());
}

void PreviewVisitor::visit(const media::AudioBook &audiobook) {
  type_ = "AUDIOBOOK ";
  visit(static_cast<const media::Media &>(audiobook));
  addRow("Voice:", audiobook.getNarrator());
  addRow("Streaming service:", audiobook.getStreamingService());
}

void PreviewVisitor::visit(const media::Ebook &ebook) {
  type_ = "EBOOK ";
  visit(static_cast<const media::Media &>(ebook));
  if (ebook.hasDrm())
    data_->addWidget(new QLabel("DRM", result_), data_->rowCount(), 0);
}

void PreviewVisitor::addRowVector(const std::string &key, const std::vector<std::string> &values) {
  if (values.size() == 0) {
    return;
  }
  data_->addWidget(new QLabel(QString::fromStdString(key), result_), data_->rowCount(), 0, Qt::AlignTop);

  data_->addWidget(
      new QLabel(QString::fromStdString(std::accumulate(
                     values.cbegin(), values.cend(), values[0],
                     [](const std::string &left, const std::string &right) { return left + "\n" + right; })),
                 result_),
      data_->rowCount() - 1, 1);
}
void PreviewVisitor::addRow(const std::string &key, const std::string &value) {
  if (value == "") return;
  data_->addWidget(new QLabel(QString::fromStdString(key), result_), data_->rowCount(), 0);
  data_->addWidget(new QLabel(QString::fromStdString(value), result_), data_->rowCount() - 1, 1);
}
void PreviewVisitor::addRow(const std::string &key, int value) {
  if (value == std::numeric_limits<int>::min()) return;
  data_->addWidget(new QLabel(QString::fromStdString(key), result_), data_->rowCount(), 0);
  data_->addWidget(new QLabel(QString::number(value), result_), data_->rowCount() - 1, 1);
}
}  // namespace gui
