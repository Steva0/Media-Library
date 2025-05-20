#ifndef MEMORY_MEDIACONTAINER_H
#define MEMORY_MEDIACONTAINER_H

#include <array>
#include <vector>
#include <QSaveFile>

#include "Media.h"
#include "Novel.h"
#include "Album.h"
#include "Movie.h"
#include "Ebook.h"
#include "AudioBook.h"
#include "Series.h"
#include "Serializer.h"

namespace memory {

class MediaContainer {
private:
    static constexpr int INDEX_ALL = 0;
    static constexpr int INDEX_NOVEL = 1;
    static constexpr int INDEX_ALBUM = 2;
    static constexpr int INDEX_MOVIE = 3;
    static constexpr int INDEX_EBOOK = 4;
    static constexpr int INDEX_AUDIOBOOK = 5;
    static constexpr int INDEX_SERIES = 6;
    static constexpr int TYPE_COUNT = 7;

    std::array<std::vector<media::Media>, TYPE_COUNT> data_;

    int detectIndex(const media::Media& media) const;
    std::vector<const media::Media*> MediaContainer::getByGroupIndex(int idx) const;

public:
    void addMedia(const media::Media& media);
    void removeMedia(const media::Media& media);
    void clear();

    std::vector<const media::Media*> filter(const media::Media& media) const;

    const std::vector<media::Media>& getAll() const;
    const std::vector<media::Media>& getByIndex(int idx) const;

    int serialize(QSaveFile& file) const;
};

} // namespace memory

#endif // MEMORY_MEDIACONTAINER_H
