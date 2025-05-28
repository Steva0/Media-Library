#ifndef MEMORY_DATABASE_H
#define MEMORY_DATABASE_H

#include "./MediaContainer.h"
#include <QString>
#include <memory>
#include <vector>

class QFile;

namespace media {
class Media;
}

namespace memory {

class Database {
private:
    MediaContainer media_container_;
    QString file_path_;

    class Deserializer {
    private:
        static std::vector<media::Media> fromJson(QFile& file);
        static std::vector<media::Media> fromXml(QFile& file);

    public:
        static std::vector<media::Media> deserialize(QFile& file);
    };

public:
    Database() = default;
    explicit Database(const QString& path);
    ~Database();

    bool open(const QString& path);
    bool close(bool save); // salva se `save == true`
    bool save();

    void addMedia(const media::Media& media);
    void removeMedia(const media::Media& media);
    void clear();

    std::vector<const media::Media*> getAll() const;
    std::vector<const media::Media*> filterMedia(const media::Media& filter) const;
};

} // namespace memory

#endif // MEMORY_DATABASE_H
