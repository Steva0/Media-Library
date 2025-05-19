#ifndef MEMORY_MEDIACONTAINER_H
#define MEMORY_MEDIACONTAINER_H

#include <array>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <functional>

#include "Media.h"
#include "Novel.h"
#include "Album.h"
#include "Movie.h"
#include "Ebook.h"
#include "AudioBook.h"
#include "Series.h"

namespace memory{

enum class MediaType {
    All = 0,
    Novel,
    Album,
    Movie,
    EBook,
    AudioBook,
    Series,
    Count // serve per la dimensione dell’array
};

class MediaContainer {
private:
    std::array<std::vector<std::shared_ptr<media::Media>>, static_cast<size_t>(MediaType::Count)> data_;

    MediaType determineType(const std::shared_ptr<media::Media>& media) const;

public:
    void addMedia(const std::shared_ptr<media::Media>& media);
    void removeMedia(const std::shared_ptr<media::Media>& media);
    void clear();

    std::vector<std::shared_ptr<media::Media>> filterByTitle(const std::string& title) const;
    std::vector<std::shared_ptr<media::Media>> filterByYear(int year) const;

    std::vector<std::shared_ptr<media::Media>> getAll() const;
    std::vector<std::shared_ptr<media::Media>> getByType(MediaType type) const;
    
    // Combinazioni di filtri
    std::vector<std::shared_ptr<media::Media>> filter(std::function<bool(const media::Media&)> predicate) const;
};
}
#endif // MEMORY_MEDIACONTAINER_H
