#ifndef MEMORY_MEDIACONTAINER_H
#define MEMORY_MEDIACONTAINER_H

#include <array>
#include <vector>
#include <QSaveFile>

#include "../Media/Media.h"
#include "../Media/Novel.h"
#include "../Media/Album.h"
#include "../Media/Movie.h"
#include "../Media/Ebook.h"
#include "../Media/AudioBook.h"
#include "../Media/Series.h"
#include "Serializer.h"

namespace memory {

class MediaContainer {
public:
    enum class Type {
        All = 0,
        Novel,
        Album,
        Movie,
        Ebook,
        AudioBook,
        Series,
        TypeCount
    };

private:
    std::array<std::vector<media::Media>, static_cast<int>(Type::TypeCount)> data_;

    Type detectType(const media::Media& media) const;
    std::vector<const media::Media*> getByGroup(Type type) const;

public:
    void addMedia(const media::Media& media);
    void removeMedia(const media::Media& media);
    void clear();

    std::vector<const media::Media*> filter(const media::Media& media) const;

    const std::vector<media::Media>& getAll() const;
    const std::vector<media::Media>& getByType(Type type) const;

    int serialize(QSaveFile& file) const;
};

} // namespace memory

#endif // MEMORY_MEDIACONTAINER_H
