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
  root_ = QJsonObject();
  root_.insert("type", "Media");

  addValue(root_, "Title", media.getTitle());
  addValue(root_, "Release", media.getRelease());
  addValue(root_, "Language", media.getLanguage());
  if (media.isFavourite())
    addFlag(root_, "Favourite");

  addStringArray(root_, "Genres", media.getGenres());
  addValue(root_, "ImagePath", media.getImgPath());
  addValue(root_, "Notes", media.getNotes());
}

void MediaJSONVisitor::visit(const media::Album &album) {
  visit(static_cast<const media::Media &>(album));
  root_["type"] = "Album";
  addValue(root_, "Band", album.getBand());
  addStringArray(root_, "BandMembers", album.getBandMembers());
  addStringArray(root_, "Songs", album.getSongs());
}

void MediaJSONVisitor::visit(const media::Movie &movie) {
  visit(static_cast<const media::Media &>(movie));
  root_["type"] = "Movie";
  addStringArray(root_, "Cast", movie.getCast());
  addValue(root_, "Length", movie.getLength());
  addValue(root_, "Universe", movie.getUniverse());
}

void MediaJSONVisitor::visit(const media::Series &series) {
  visit(static_cast<const media::Movie &>(series));
  root_["type"] = "Series";
  addValue(root_, "Episodes", series.getEpisodes());
  addValue(root_, "Seasons", series.getSeasons());
  if (series.hasEnded())
    addFlag(root_, "Ended");
}

void MediaJSONVisitor::visit(const media::Novel &novel) {
  visit(static_cast<const media::Media &>(novel));
  root_["type"] = "Novel";
  addValue(root_, "Author", novel.getAuthor());
  addValue(root_, "Publisher", novel.getPublisher());
  addValue(root_, "Pages", novel.getPages());
  addValue(root_, "Series", novel.getSeries());
  addValue(root_, "ISBN", novel.getIsbn());
}

void MediaJSONVisitor::visit(const media::AudioBook &audioBook) {
  visit(static_cast<const media::Novel &>(audioBook));
  root_["type"] = "AudioBook";
  addValue(root_, "Narrator", audioBook.getNarrator());
  addValue(root_, "Service", audioBook.getStreamingService());
}

void MediaJSONVisitor::visit(const media::Ebook &ebook) {
  visit(static_cast<const media::Novel &>(ebook));
  root_["type"] = "Ebook";
  addValue(root_, "Bytes", ebook.getFileSizeBytes());
  if (ebook.hasDrm())
    addFlag(root_, "DRM");
}

}  // namespace memory
