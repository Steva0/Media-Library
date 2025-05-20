#include "MediaContainer.h"

namespace memory {

void MediaContainer::addMedia(const std::shared_ptr<media::Media>& media) {
    if (!media) return;

    data_[static_cast<size_t>(MediaType::All)].push_back(media);

    MediaType type = determineType(media);
    if (type != MediaType::All) {
        data_[static_cast<size_t>(type)].push_back(media);
    }
}

void MediaContainer::removeMedia(const std::shared_ptr<media::Media>& media) {
    if (!media) return;

    for (auto& vec : data_) {
        vec.erase(std::remove_if(vec.begin(), vec.end(),
            [&](const std::shared_ptr<media::Media>& m) {
                return typeid(*m) == typeid(*media) && *m == *media;
            }), vec.end());
    }
}

void MediaContainer::clear() {
    for (auto& vec : data_) {
        vec.clear();
    }
}

std::vector<std::shared_ptr<media::Media>> MediaContainer::getAll() const {
    return data_[static_cast<size_t>(MediaType::All)];
}

std::vector<std::shared_ptr<media::Media>> MediaContainer::getByType(MediaType type) const {
    return data_[static_cast<size_t>(type)];
}

std::vector<std::shared_ptr<media::Media>> MediaContainer::getByTypeAndSubtype(MediaType type) const {
    std::vector<std::shared_ptr<media::Media>> result;

    switch (type) {
        case MediaType::Novel:
            result.insert(result.end(), data_[static_cast<size_t>(MediaType::Novel)].begin(), data_[static_cast<size_t>(MediaType::Novel)].end());
            result.insert(result.end(), data_[static_cast<size_t>(MediaType::EBook)].begin(), data_[static_cast<size_t>(MediaType::EBook)].end());
            result.insert(result.end(), data_[static_cast<size_t>(MediaType::AudioBook)].begin(), data_[static_cast<size_t>(MediaType::AudioBook)].end());
            break;
        case MediaType::Movie:
            result.insert(result.end(), data_[static_cast<size_t>(MediaType::Movie)].begin(), data_[static_cast<size_t>(MediaType::Movie)].end());
            result.insert(result.end(), data_[static_cast<size_t>(MediaType::Series)].begin(), data_[static_cast<size_t>(MediaType::Series)].end());
            break;
        case MediaType::All:
            result = data_[0];
            break;
        default:
            result = data_[static_cast<size_t>(type)];
            break;
    }

    return result;
}

MediaType MediaContainer::determineType(const std::shared_ptr<media::Media>& media) const {
    if (std::dynamic_pointer_cast<media::Series>(media)) return MediaType::Series;
    if (std::dynamic_pointer_cast<media::Movie>(media)) return MediaType::Movie;
    if (std::dynamic_pointer_cast<media::AudioBook>(media)) return MediaType::AudioBook;
    if (std::dynamic_pointer_cast<media::Ebook>(media)) return MediaType::EBook;
    if (std::dynamic_pointer_cast<media::Novel>(media)) return MediaType::Novel;
    if (std::dynamic_pointer_cast<media::Album>(media)) return MediaType::Album;
    return MediaType::All;
}

std::vector<std::shared_ptr<media::Media>> MediaContainer::filter(const std::shared_ptr<media::Media>& media) const {
    if (auto m = std::dynamic_pointer_cast<media::Series>(media)) return filters(m);
    if (auto m = std::dynamic_pointer_cast<media::Movie>(media)) return filters(m);
    if (auto m = std::dynamic_pointer_cast<media::AudioBook>(media)) return filters(m);
    if (auto m = std::dynamic_pointer_cast<media::Ebook>(media)) return filters(m);
    if (auto m = std::dynamic_pointer_cast<media::Novel>(media)) return filters(m);
    if (auto m = std::dynamic_pointer_cast<media::Album>(media)) return filters(m);
    return filters(media);
}

std::vector<std::shared_ptr<media::Media>> MediaContainer::filters(const std::shared_ptr<media::Media>& media) const {
    auto allMedia = getAll();
    return media->filter(allMedia);
}

std::vector<std::shared_ptr<media::Media>> MediaContainer::filters(const std::shared_ptr<media::Novel>& novel) const {
    auto media = getByTypeAndSubtype(MediaType::Novel);
    std::vector<std::shared_ptr<media::Novel>> allNovel;
    for (const auto& m : media)
        if (auto ptr = std::dynamic_pointer_cast<media::Novel>(m)) allNovel.push_back(ptr);
    std::vector<std::shared_ptr<media::Media>> result;
    for (const auto& m : novel->filter(allNovel)) result.push_back(m);
    return result;
}

std::vector<std::shared_ptr<media::Media>> MediaContainer::filters(const std::shared_ptr<media::Album>& album) const {
    auto media = getByType(MediaType::Album);
    std::vector<std::shared_ptr<media::Album>> allAlbum;
    for (const auto& m : media)
        if (auto ptr = std::dynamic_pointer_cast<media::Album>(m)) allAlbum.push_back(ptr);
    std::vector<std::shared_ptr<media::Media>> result;
    for (const auto& m : album->filter(allAlbum)) result.push_back(m);
    return result;
}

std::vector<std::shared_ptr<media::Media>> MediaContainer::filters(const std::shared_ptr<media::Movie>& movie) const {
    auto media = getByTypeAndSubtype(MediaType::Movie);
    std::vector<std::shared_ptr<media::Movie>> allMovie;
    for (const auto& m : media)
        if (auto ptr = std::dynamic_pointer_cast<media::Movie>(m)) allMovie.push_back(ptr);
    std::vector<std::shared_ptr<media::Media>> result;
    for (const auto& m : movie->filter(allMovie)) result.push_back(m);
    return result;
}

std::vector<std::shared_ptr<media::Media>> MediaContainer::filters(const std::shared_ptr<media::Ebook>& ebook) const {
    auto media = getByType(MediaType::EBook);
    std::vector<std::shared_ptr<media::Ebook>> allEbook;
    for (const auto& m : media)
        if (auto ptr = std::dynamic_pointer_cast<media::Ebook>(m)) allEbook.push_back(ptr);
    std::vector<std::shared_ptr<media::Media>> result;
    for (const auto& m : ebook->filter(allEbook)) result.push_back(m);
    return result;
}

std::vector<std::shared_ptr<media::Media>> MediaContainer::filters(const std::shared_ptr<media::AudioBook>& audiobook) const {
    auto media = getByType(MediaType::AudioBook);
    std::vector<std::shared_ptr<media::AudioBook>> allAudio;
    for (const auto& m : media)
        if (auto ptr = std::dynamic_pointer_cast<media::AudioBook>(m)) allAudio.push_back(ptr);
    std::vector<std::shared_ptr<media::Media>> result;
    for (const auto& m : audiobook->filter(allAudio)) result.push_back(m);
    return result;
}

std::vector<std::shared_ptr<media::Media>> MediaContainer::filters(const std::shared_ptr<media::Series>& series) const {
    auto media = getByType(MediaType::Series);
    std::vector<std::shared_ptr<media::Series>> allSeries;
    for (const auto& m : media)
        if (auto ptr = std::dynamic_pointer_cast<media::Series>(m)) allSeries.push_back(ptr);
    std::vector<std::shared_ptr<media::Media>> result;
    for (const auto& m : series->filter(allSeries)) result.push_back(m);
    return result;
}

int MediaContainer::serialize(QSaveFile& file) const {
    return Serializer::Serialize(getAll(), file);
}

} // namespace memory
