#include "Database.h"
#include "Serializer.h"

#include "../Media/Media.h"


#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDomDocument>
#include <QTextStream>

namespace memory {

Database::~Database() {
    close(false);
}

Database::Database(const QString& path) {
    open(path);
}

bool Database::open(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    media_container_.clear();
    const auto list = Deserializer::deserialize(file);
    for (const auto& media : list) {
        media_container_.addMedia(media);
    }

    file_path_ = path;
    return true;
}

bool Database::close(bool save_on_exit) {
    if (save_on_exit)
        return save();

    media_container_.clear();
    file_path_.clear();
    return true;
}

bool Database::save() {
    if (file_path_.isEmpty())
        return false;

    QFile file(file_path_);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
        return false;

    const int result = Serializer::serialize(media_container_.getAll(), file);
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

std::vector<media::Media> Database::Deserializer::deserialize(QFile& file) {
    QString fileName = file.fileName().toLower();
    if (fileName.endsWith(".json")) {
        return fromJson(file);
    } else {
        return fromXml(file);
    }
}

std::vector<media::Media> Database::Deserializer::fromJson(QFile& file) {
    std::vector<media::Media> result;

    return result;
}

std::vector<media::Media> Database::Deserializer::fromXml(QFile& file) {
    std::vector<media::Media> result;

    return result;
}

} // namespace memory
