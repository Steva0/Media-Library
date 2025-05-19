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

std::vector<std::shared_ptr<media::Media>> MediaContainer::filterByTitle(const std::string& title) const {
    return filter([&](const media::Media& m) {
        return m.getTitle() == title;
    });
}

std::vector<std::shared_ptr<media::Media>> MediaContainer::filterByYear(int year) const {
    return filter([&](const media::Media& m) {
        return m.getRelease() == year;
    });
}

std::vector<std::shared_ptr<media::Media>> MediaContainer::getAll() const {
    return data_[static_cast<size_t>(MediaType::All)];
}

std::vector<std::shared_ptr<media::Media>> MediaContainer::getByType(MediaType type) const {
    return data_[static_cast<size_t>(type)];
}

std::vector<std::shared_ptr<media::Media>> MediaContainer::filter(std::function<bool(const media::Media&)> predicate) const {
    std::vector<std::shared_ptr<media::Media>> result;
    for (const auto& media : data_[static_cast<size_t>(MediaType::All)]) {
        if (predicate(*media)) {
            result.push_back(media);
        }
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
}