#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QTextStream>

#include "../Media/Album.h"
#include "../Media/AudioBook.h"
#include "../Media/Ebook.h"
#include "../Media/Media.h"
#include "../Media/Movie.h"
#include "../Media/Novel.h"
#include "../Media/Series.h"
#include "FileManager.h"
#include "Serializer.h"

namespace memory {
const std::array<std::string, 2> FileManager::kAcceptedExtensions{"xml", "json"};

FileManager::~FileManager() { close(); }

std::vector<std::unique_ptr<media::Media>> FileManager::deserialize(const QString& path) {
  QFile file(path);
  if (!file.exists()) {
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      return {};
    }
    file.close();
  }

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))  // return false;
    return {};

  std::vector<std::unique_ptr<media::Media>> result;
  if (file.size() > 0) {
    const QString fileName = file.fileName().toLower();
    if (fileName.endsWith(".json")) {
      result = fromJson(file);
    } else {
      result = fromXml(file);
    }
  }

  file_path_ = path;
  file.close();
  return result;
}

void FileManager::close() { file_path_.clear(); }
bool FileManager::close(const std::vector<const media::Media*>& save_data) {
  bool done = save(save_data);
  file_path_.clear();
  return done;
}

bool FileManager::save(const std::vector<const media::Media*>& data, const QString& path) {
  QString savePath = path.isEmpty() ? file_path_ : path;
  if (savePath.isEmpty()) return false;

  if (!path.isEmpty()) file_path_ = path;

  QFile file(savePath);

  int result = Serializer::serialize(data, file);
  file.close();
  return result == 0;
}

static std::vector<std::string> readStringArray(const QJsonObject& obj, const QString& key) {
  std::vector<std::string> result;
  if (obj.contains(key) && obj[key].isArray()) {
    QJsonArray array = obj[key].toArray();
    for (const auto& val : array) result.push_back(val.toString().toStdString());
  }
  return result;
}

std::vector<std::unique_ptr<media::Media>> FileManager::fromJson(QFile& file) {
  QByteArray data = file.readAll();
  QJsonParseError error;
  QJsonDocument doc = QJsonDocument::fromJson(data, &error);

  if (error.error != QJsonParseError::NoError || !doc.isArray())  // return;
    return {};

  std::vector<std::unique_ptr<media::Media>> result;

  QJsonArray array = doc.array();
  for (const auto& value : array) {
    if (!value.isObject()) continue;
    QJsonObject obj = value.toObject();
    if (!obj.contains("type") || !obj.contains("Title")) continue;

    QString type = obj["type"].toString();

    std::unique_ptr<media::Media> media;

    // Campi comuni
    std::string title = obj["Title"].toString().toStdString();
    int release = obj.contains("Release") ? obj["Release"].toInt() : std::numeric_limits<int>::min();
    std::string language = obj.contains("Language") ? obj["Language"].toString().toStdString() : "";
    std::vector<std::string> genres =
        obj.contains("Genres") ? readStringArray(obj, "Genres") : std::vector<std::string>();
    std::string imagePath = obj.contains("ImagePath") ? obj["ImagePath"].toString().toStdString() : "";
    std::string notes = obj.contains("Notes") ? obj["Notes"].toString().toStdString() : "";
    bool favourite = obj.contains("Favourite") ? obj["Favourite"].toBool() : false;

    if (type == "Album") {
      std::string band = obj.contains("Band") ? obj["Band"].toString().toStdString() : "";
      auto bandMembers = obj.contains("BandMembers") ? readStringArray(obj, "BandMembers") : std::vector<std::string>();
      auto songs = obj.contains("Songs") ? readStringArray(obj, "Songs") : std::vector<std::string>();
      media = std::make_unique<media::Album>(title, release, language, favourite, genres, imagePath, notes, band,
                                             bandMembers, songs);
    } else if (type == "Movie") {
      auto cast = obj.contains("Cast") ? readStringArray(obj, "Cast") : std::vector<std::string>();
      int length = obj.contains("Length") ? obj["Length"].toInt() : std::numeric_limits<int>::min();
      std::string universe = obj.contains("Universe") ? obj["Universe"].toString().toStdString() : "";
      media = std::make_unique<media::Movie>(title, release, language, favourite, genres, imagePath, notes, cast,
                                             length, universe);
    } else if (type == "Series") {
      auto cast = obj.contains("Cast") ? readStringArray(obj, "Cast") : std::vector<std::string>();
      int length = obj.contains("Length") ? obj["Length"].toInt() : std::numeric_limits<int>::min();
      std::string universe = obj.contains("Universe") ? obj["Universe"].toString().toStdString() : "";
      int episodes = obj.contains("Episodes") ? obj["Episodes"].toInt() : std::numeric_limits<int>::min();
      int seasons = obj.contains("Seasons") ? obj["Seasons"].toInt() : std::numeric_limits<int>::min();
      bool ended = obj.contains("Ended") ? obj["Ended"].toBool() : false;
      media = std::make_unique<media::Series>(title, release, language, favourite, genres, imagePath, notes, cast,
                                              length, universe, episodes, seasons, ended);
    } else if (type == "Novel") {
      std::string author = obj.contains("Author") ? obj["Author"].toString().toStdString() : "";
      std::string publisher = obj.contains("Publisher") ? obj["Publisher"].toString().toStdString() : "";
      int pages = obj.contains("Pages") ? obj["Pages"].toInt() : std::numeric_limits<int>::min();
      std::string series = obj.contains("Series") ? obj["Series"].toString().toStdString() : "";
      std::string isbn = obj.contains("ISBN") ? obj["ISBN"].toString().toStdString() : "";
      media = std::make_unique<media::Novel>(title, release, language, favourite, genres, imagePath, notes, author,
                                             publisher, pages, series, isbn);
    } else if (type == "AudioBook") {
      std::string author = obj.contains("Author") ? obj["Author"].toString().toStdString() : "";
      std::string publisher = obj.contains("Publisher") ? obj["Publisher"].toString().toStdString() : "";
      int pages = obj.contains("Pages") ? obj["Pages"].toInt() : std::numeric_limits<int>::min();
      std::string series = obj.contains("Series") ? obj["Series"].toString().toStdString() : "";
      std::string isbn = obj.contains("ISBN") ? obj["ISBN"].toString().toStdString() : "";
      std::string narrator = obj.contains("Narrator") ? obj["Narrator"].toString().toStdString() : "";
      std::string service = obj.contains("Service") ? obj["Service"].toString().toStdString() : "";
      media = std::make_unique<media::AudioBook>(title, release, language, favourite, genres, imagePath, notes, author,
                                                 publisher, pages, series, isbn, narrator, service);
    } else if (type == "Ebook") {
      std::string author = obj.contains("Author") ? obj["Author"].toString().toStdString() : "";
      std::string publisher = obj.contains("Publisher") ? obj["Publisher"].toString().toStdString() : "";
      int pages = obj.contains("Pages") ? obj["Pages"].toInt() : std::numeric_limits<int>::min();
      std::string series = obj.contains("Series") ? obj["Series"].toString().toStdString() : "";
      std::string isbn = obj.contains("ISBN") ? obj["ISBN"].toString().toStdString() : "";
      int bytes = obj.contains("Bytes") ? obj["Bytes"].toInt() : std::numeric_limits<int>::min();
      bool drm = obj.contains("DRM") ? obj["DRM"].toBool() : false;
      media = std::make_unique<media::Ebook>(title, release, language, favourite, genres, imagePath, notes, author,
                                             publisher, pages, series, isbn, bytes, drm);
    } else {
      continue;  // tipo sconosciuto
    }

    result.push_back(std::move(media));
  }

  return result;
}

std::vector<std::unique_ptr<media::Media>> FileManager::fromXml(QFile& file) {
  QDomDocument doc;
  if (!doc.setContent(&file)) {
    file.close();
    return {};
  }
  file.close();

  QDomElement root = doc.documentElement();
  QDomNodeList mediaNodes = root.childNodes();

  std::vector<std::unique_ptr<media::Media>> result;

  for (int i = 0; i < mediaNodes.count(); ++i) {
    QDomElement el = mediaNodes.at(i).toElement();
    if (el.isNull()) continue;

    QString type = el.tagName();

    std::string title = el.firstChildElement("Title").text().toStdString();
    if (title.empty()) continue;

    int release = el.firstChildElement("Release").isNull() ? std::numeric_limits<int>::min()
                                                           : el.firstChildElement("Release").text().toInt();
    std::string language = el.firstChildElement("Language").text().toStdString();
    std::string imagePath = el.firstChildElement("ImagePath").text().toStdString();
    std::string notes = el.firstChildElement("Notes").text().toStdString();
    bool favourite = !el.firstChildElement("Favourite").isNull();

    std::vector<std::string> genres;
    QDomElement genresEl = el.firstChildElement("Genres");
    for (QDomElement genre = genresEl.firstChildElement("Genre"); !genre.isNull();
         genre = genre.nextSiblingElement("Genre")) {
      genres.push_back(genre.text().toStdString());
    }

    std::unique_ptr<media::Media> media;

    if (type == "Album") {
      std::string band = el.firstChildElement("Band").text().toStdString();
      std::vector<std::string> members;
      QDomElement membersEl = el.firstChildElement("BandMembers");
      for (QDomElement m = membersEl.firstChildElement("Member"); !m.isNull(); m = m.nextSiblingElement("Member"))
        members.push_back(m.text().toStdString());

      std::vector<std::string> songs;
      QDomElement songsEl = el.firstChildElement("Songs");
      for (QDomElement s = songsEl.firstChildElement("Song"); !s.isNull(); s = s.nextSiblingElement("Song"))
        songs.push_back(s.text().toStdString());

      media = std::make_unique<media::Album>(title, release, language, favourite, genres, imagePath, notes, band,
                                             members, songs);
    } else if (type == "Movie" || type == "Series") {
      std::vector<std::string> cast;
      QDomElement castEl = el.firstChildElement("Cast");
      for (QDomElement a = castEl.firstChildElement("Act"); !a.isNull(); a = a.nextSiblingElement("Act"))
        cast.push_back(a.text().toStdString());

      int length = el.firstChildElement("Length").isNull() ? std::numeric_limits<int>::min()
                                                           : el.firstChildElement("Length").text().toInt();
      std::string universe = el.firstChildElement("Universe").text().toStdString();

      if (type == "Series") {
        int episodes = el.firstChildElement("Episodes").isNull() ? std::numeric_limits<int>::min()
                                                                 : el.firstChildElement("Episodes").text().toInt();
        int seasons = el.firstChildElement("Seasons").isNull() ? std::numeric_limits<int>::min()
                                                               : el.firstChildElement("Seasons").text().toInt();
        bool ended = !el.firstChildElement("Ended").isNull();

        media = std::make_unique<media::Series>(title, release, language, favourite, genres, imagePath, notes, cast,
                                                length, universe, episodes, seasons, ended);
      } else {
        media = std::make_unique<media::Movie>(title, release, language, favourite, genres, imagePath, notes, cast,
                                               length, universe);
      }
    } else if (type == "Novel" || type == "AudioBook" || type == "Ebook") {
      std::string author = el.firstChildElement("Author").text().toStdString();
      std::string publisher = el.firstChildElement("Publisher").text().toStdString();
      int pages = el.firstChildElement("Pages").isNull() ? std::numeric_limits<int>::min()
                                                         : el.firstChildElement("Pages").text().toInt();
      std::string series = el.firstChildElement("Series").text().toStdString();
      std::string isbn = el.firstChildElement("ISBN").text().toStdString();

      if (type == "AudioBook") {
        std::string narrator = el.firstChildElement("Narrator").text().toStdString();
        std::string service = el.firstChildElement("Service").text().toStdString();

        media = std::make_unique<media::AudioBook>(title, release, language, favourite, genres, imagePath, notes,
                                                   author, publisher, pages, series, isbn, narrator, service);
      } else if (type == "Ebook") {
        int bytes = el.firstChildElement("Bytes").isNull() ? std::numeric_limits<int>::min()
                                                           : el.firstChildElement("Bytes").text().toInt();
        bool drm = !el.firstChildElement("DRM").isNull();

        media = std::make_unique<media::Ebook>(title, release, language, favourite, genres, imagePath, notes, author,
                                               publisher, pages, series, isbn, bytes, drm);
      } else {
        media = std::make_unique<media::Novel>(title, release, language, favourite, genres, imagePath, notes, author,
                                               publisher, pages, series, isbn);
      }
    } else {
      continue;  // tipo sconosciuto
    }

    result.push_back(std::move(media));
  }

  return result;
}

}  // namespace memory
