#ifndef MEMORY_MEDIACONTAINER_H
#define MEMORY_MEDIACONTAINER_H

#include <array>
#include <vector>
#include <memory>
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
private:
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

    std::array<std::vector<std::unique_ptr<media::Media>>, static_cast<size_t>(Type::TypeCount)> data_;

    Type detectType(const media::Media& media) const;

    std::vector<const media::Media*> getByType(Type type) const;
    std::vector<const media::Media*> getByGroup(Type type) const;

public:
    void addMedia(const media::Media& media);
    void removeMedia(const media::Media& media);
    void clear();

    std::vector<const media::Media*> filter(const media::Media& media) const;

    std::vector<const media::Media*> getAll() const;

    int serialize(QSaveFile& file) const;
};

} // namespace memory

#endif // MEMORY_MEDIACONTAINER_H
