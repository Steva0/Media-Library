#include "MediaJSONVisitor.h"

#include "../Media/Album.h"
#include "../Media/AudioBook.h"
#include "../Media/Ebook.h"
#include "../Media/Media.h"
#include "../Media/Movie.h"
#include "../Media/Novel.h"
#include "../Media/Series.h"

namespace memory {

QJsonDocument MediaJSONVisitor::getDocument() const {
  return QJsonDocument(root_);
}

void MediaJSONVisitor::addValue(QJsonObject &obj, const QString &key, const std::string &value) {
  obj.insert(key, QString::fromStdString(value));
}
void MediaJSONVisitor::addValue(QJsonObject &obj, const QString &key, int value) {
  obj.insert(key, value);
}
void MediaJSONVisitor::addValue(QJsonObject &obj, const QString &key, unsigned int value) {
  obj.insert(key, static_cast<int>(value));
}
void MediaJSONVisitor::addFlag(QJsonObject &obj, const QString &key) {
  obj.insert(key, true);
}
void MediaJSONVisitor::addStringArray(QJsonObject &obj, const QString &key, const std::vector<std::string> &vec) {
  QJsonArray array;
  for (const auto &v : vec)
    array.append(QString::fromStdString(v));
  obj.insert(key, array);
}

void MediaJSONVisitor::visit(const media::Media &media) {
  if (media.getTitle().empty()) {
    return;
  }
  root_ = QJsonObject();
  root_.insert("type", "Media");

  addValue(root_, "Title", media.getTitle());

  // Only add if not empty
  if (media.getRelease() != std::numeric_limits<int>::min())
    addValue(root_, "Release", media.getRelease());
  if (media.getLanguage() != "")
    addValue(root_, "Language", media.getLanguage());
  if (media.isFavourite())
    addFlag(root_, "Favourite");

  if (!media.getGenres().empty())
    addStringArray(root_, "Genres", media.getGenres());
  if (media.getImgPath() != "")
    addValue(root_, "ImagePath", media.getImgPath());
  if (media.getNotes() != "")
    addValue(root_, "Notes", media.getNotes());
}

void MediaJSONVisitor::visit(const media::Album &album) {
  if (album.getTitle().empty()) {
    return;
  }
  visit(static_cast<const media::Media &>(album));
  root_["type"] = "Album";
  if (album.getBand() != "")
    addValue(root_, "Band", album.getBand());
  if (!album.getBandMembers().empty())
    addStringArray(root_, "BandMembers", album.getBandMembers());
  if (!album.getSongs().empty())
    addStringArray(root_, "Songs", album.getSongs());
}

void MediaJSONVisitor::visit(const media::Movie &movie) {
  if (movie.getTitle().empty()) {
    return;
  }
  visit(static_cast<const media::Media &>(movie));
  root_["type"] = "Movie";
  if (!movie.getCast().empty())
    addStringArray(root_, "Cast", movie.getCast());
  if (movie.getLength() != std::numeric_limits<int>::min())
    addValue(root_, "Length", movie.getLength());
  if (movie.getUniverse() != "")
    addValue(root_, "Universe", movie.getUniverse());
}

void MediaJSONVisitor::visit(const media::Series &series) {
  if (series.getTitle().empty()) {
    return;
  }
  visit(static_cast<const media::Movie &>(series));
  root_["type"] = "Series";
  if (series.getEpisodes() != std::numeric_limits<int>::min())
    addValue(root_, "Episodes", series.getEpisodes());
  if (series.getSeasons() != std::numeric_limits<int>::min())
    addValue(root_, "Seasons", series.getSeasons());
  if (series.hasEnded())
    addFlag(root_, "Ended");
}

void MediaJSONVisitor::visit(const media::Novel &novel) {
  if (novel.getTitle().empty()) {
    return;
  }
  visit(static_cast<const media::Media &>(novel));
  root_["type"] = "Novel";
  if (novel.getAuthor() != "")
    addValue(root_, "Author", novel.getAuthor());
  if (novel.getPublisher() != "")
    addValue(root_, "Publisher", novel.getPublisher());
  if (novel.getPages() != std::numeric_limits<int>::min())
    addValue(root_, "Pages", novel.getPages());
  if (novel.getSeries() != "")
    addValue(root_, "Series", novel.getSeries());
  if (novel.getIsbn() != "")
    addValue(root_, "ISBN", novel.getIsbn());
}

void MediaJSONVisitor::visit(const media::AudioBook &audioBook) {
  if (audioBook.getTitle().empty()) {
    return;
  }
  visit(static_cast<const media::Novel &>(audioBook));
  root_["type"] = "AudioBook";
  if (audioBook.getNarrator() != "")
    addValue(root_, "Narrator", audioBook.getNarrator());
  if (audioBook.getStreamingService() != "")
    addValue(root_, "Service", audioBook.getStreamingService());
}

void MediaJSONVisitor::visit(const media::Ebook &ebook) {
  if (ebook.getTitle().empty()) {
    return;
  }
  visit(static_cast<const media::Novel &>(ebook));
  root_["type"] = "Ebook";
  if (ebook.getFileSizeBytes() != std::numeric_limits<int>::min())
    addValue(root_, "Bytes", ebook.getFileSizeBytes());
  if (ebook.hasDrm())
    addFlag(root_, "DRM");
}

}  // namespace memory
