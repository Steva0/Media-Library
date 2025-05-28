#include "Database.h"
#include "Serializer.h"
#include "../Media/Media.h"
#include "../Media/Album.h"
#include "../Media/AudioBook.h"
#include "../Media/Ebook.h"
#include "../Media/Movie.h"
#include "../Media/Novel.h"
#include "../Media/Series.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDomDocument>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonParseError>


namespace memory {

Database::~Database() {
    close(false);
}

Database::Database(const QString& path) {
    open(path);
}

bool Database::open(const QString& path) {
    QFile file(path);
    if (!file.exists()) {
        // Create an empty file if it doesn't exist
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            return false;
        }
        file.close();
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    media_container_.clear();

    // Deserialize only if file is not empty
    if (file.size() > 0) {
        const QString fileName = file.fileName().toLower();
        fileName.endsWith(".json") ? fromJson(file) : fromXml(file);
    }

    file_path_ = path;
    file.close();
    return true;
}

bool Database::close(bool save_on_exit) {
    bool ok = true;
    if (save_on_exit)
        ok = save();

    media_container_.clear();
    file_path_.clear();
    return ok;
}

bool Database::save(const QString& path) {
    QString savePath = path.isEmpty() ? file_path_ : path;
    if (savePath.isEmpty())
        return false;

    if (!path.isEmpty())
        file_path_ = path;

    QFile file(savePath);

    int result = Serializer::serialize(media_container_.getAll(), file);
    file.close();
    return result == 0;
}

std::vector<const media::Media*> Database::getAll() const {
    return media_container_.getAll();
}

std::vector<const media::Media*> Database::filterMedia(const media::Media& filter) const {
    return media_container_.filter(filter);
}

void Database::addMedia(const media::Media& media) {
    media_container_.addMedia(media);
}

void Database::removeMedia(const media::Media& media) {
    media_container_.removeMedia(media);
}

void Database::clear() {
    media_container_.clear();
}

static std::vector<std::string> readStringArray(const QJsonObject& obj, const QString& key) {
    std::vector<std::string> result;
    if (obj.contains(key) && obj[key].isArray()) {
        QJsonArray array = obj[key].toArray();
        for (const auto& val : array)
            result.push_back(val.toString().toStdString());
    }
    return result;
}

void Database::fromJson(QFile& file) {
    QByteArray data = file.readAll();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError || !doc.isArray()) return;

    QJsonArray array = doc.array();
    for (const auto& value : array) {
        if (!value.isObject()) continue;
        QJsonObject obj = value.toObject();
        if (!obj.contains("type")) continue;

        QString type = obj["type"].toString();

        std::unique_ptr<media::Media> media;

        // Campi comuni 
        std::string title = obj["Title"].toString().toStdString();
        int release = obj["Release"].toInt();
        std::string language = obj["Language"].toString().toStdString();
        std::vector<std::string> genres = readStringArray(obj, "Genres");
        std::string imagePath = obj["ImagePath"].toString().toStdString();
        std::string notes = obj["Notes"].toString().toStdString();
        bool favourite = obj.contains("Favourite") && obj["Favourite"].toBool();

        if (type == "Album") {
            std::string band = obj["Band"].toString().toStdString();
            auto bandMembers = readStringArray(obj, "BandMembers");
            auto songs = readStringArray(obj, "Songs");
            media = std::make_unique<media::Album>(title, release, language, favourite, genres, imagePath, notes, band, bandMembers, songs);
        }
        else if (type == "Movie") {
            auto cast = readStringArray(obj, "Cast");
            int length = obj["Length"].toInt();
            std::string universe = obj["Universe"].toString().toStdString();
            media = std::make_unique<media::Movie>(title, release, language, favourite, genres, imagePath, notes, cast, length, universe);
        }
        else if (type == "Series") {
            auto cast = readStringArray(obj, "Cast");
            int length = obj["Length"].toInt();
            std::string universe = obj["Universe"].toString().toStdString();
            int episodes = obj["Episodes"].toInt();
            int seasons = obj["Seasons"].toInt();
            bool ended = obj.contains("Ended") && obj["Ended"].toBool();
            media = std::make_unique<media::Series>(title, release, language, favourite, genres, imagePath, notes, cast, length, universe, episodes, seasons, ended);
        }
        else if (type == "Novel") {
            std::string author = obj["Author"].toString().toStdString();
            std::string publisher = obj["Publisher"].toString().toStdString();
            int pages = obj["Pages"].toInt();
            std::string series = obj["Series"].toString().toStdString();
            std::string isbn = obj["ISBN"].toString().toStdString();
            media = std::make_unique<media::Novel>(title, release, language, favourite, genres, imagePath, notes, author, publisher, pages, series, isbn);
        }
        else if (type == "AudioBook") {
            std::string author = obj["Author"].toString().toStdString();
            std::string publisher = obj["Publisher"].toString().toStdString();
            int pages = obj["Pages"].toInt();
            std::string series = obj["Series"].toString().toStdString();
            std::string isbn = obj["ISBN"].toString().toStdString();
            std::string narrator = obj["Narrator"].toString().toStdString();
            std::string service = obj["Service"].toString().toStdString();
            media = std::make_unique<media::AudioBook>(title, release, language, favourite, genres, imagePath, notes, author, publisher, pages, series, isbn, narrator, service);
        }
        else if (type == "Ebook") {
            std::string author = obj["Author"].toString().toStdString();
            std::string publisher = obj["Publisher"].toString().toStdString();
            int pages = obj["Pages"].toInt();
            std::string series = obj["Series"].toString().toStdString();
            std::string isbn = obj["ISBN"].toString().toStdString();
            int bytes = obj["Bytes"].toInt();
            bool drm = obj.contains("DRM") && obj["DRM"].toBool();
            media = std::make_unique<media::Ebook>(title, release, language, favourite, genres, imagePath, notes, author, publisher, pages, series, isbn, bytes, drm);
        }
        else {
            continue;  // tipo sconosciuto
        }

        if (media)
            media_container_.addMedia(*media);
    }
}

void Database::fromXml(QFile& file) {
}


} // namespace memory