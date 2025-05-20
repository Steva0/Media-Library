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

    std::vector<std::shared_ptr<media::Media>> getAll() const;
    std::vector<std::shared_ptr<media::Media>> getByType(MediaType type) const;
    std::vector<std::shared_ptr<media::Media>> getByTypeAndSubtype(MediaType type) const;

    //Sezione filtri
    std::vector<std::shared_ptr<media::Media>> filter(const std::shared_ptr<media::Media>& media) const;
    std::vector<std::shared_ptr<media::Novel>> filter(const std::shared_ptr<media::Novel>& novel) const;
    std::vector<std::shared_ptr<media::Album>> filter(const std::shared_ptr<media::Album>& album) const;
    std::vector<std::shared_ptr<media::Movie>> filter(const std::shared_ptr<media::Movie>& movie) const;
    std::vector<std::shared_ptr<media::Ebook>> filter(const std::shared_ptr<media::Ebook>& ebook) const;
    std::vector<std::shared_ptr<media::AudioBook>> filter(const std::shared_ptr<media::AudioBook>& audiobook) const;
    std::vector<std::shared_ptr<media::Series>> filter(const std::shared_ptr<media::Series>& series) const;

};
}
#endif // MEMORY_MEDIACONTAINER_H
