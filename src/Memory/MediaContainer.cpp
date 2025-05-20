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
            result = data_[0]; // Tutti i media
            break;

        default:
            // Ritorna il vettore corrispondente solo per quel tipo specifico
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

std::vector<std::shared_ptr<media::Media>> MediaContainer::filter(const std::shared_ptr<media::Media>& media) const{
    auto allMedia = getAll();
    return media->filter(allMedia);
}

std::vector<std::shared_ptr<media::Novel>> MediaContainer::filter(const std::shared_ptr<media::Novel>& novel) const{
    auto media= getByTypeAndSubtype(MediaType::Novel);
    std::vector<std::shared_ptr<media::Novel>> allNovel;
    for (const auto& mediaPtr : media) {
        auto novelPtr = std::dynamic_pointer_cast<media::Novel>(mediaPtr);
        if (novelPtr) {
            allNovel.push_back(novelPtr);
        }
    }
    return novel->filter(allNovel);
}