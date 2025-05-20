#include "MediaContainer.h"
#include <typeinfo>
#include <algorithm>

namespace memory {

void MediaContainer::addMedia(const media::Media& media) { 
    data_[INDEX_ALL].push_back(media);  

    if (detectIndex(media) == INDEX_ALL) {
        return; // Media already exists in the container
    } else {
        data_[detectIndex(media)].push_back(media);
    }
}

int MediaContainer::detectIndex(const media::Media& media) const {
    if (dynamic_cast<const media::Series*>(&media)) {
        return INDEX_SERIES;
    } else if (dynamic_cast<const media::AudioBook*>(&media)) {
        return INDEX_AUDIOBOOK;
    } else if (dynamic_cast<const media::Ebook*>(&media)) {
        return INDEX_EBOOK;
    } else if (dynamic_cast<const media::Movie*>(&media)) {
        return INDEX_MOVIE;
    } else if (dynamic_cast<const media::Album*>(&media)) {
        return INDEX_ALBUM;
    } else if (dynamic_cast<const media::Novel*>(&media)) {
        return INDEX_NOVEL;
    }
    return INDEX_ALL; // Default case
}

void MediaContainer::removeMedia(const media::Media& media) {
    for (auto& vec : data_) {
        vec.erase(std::remove_if(vec.begin(), vec.end(),
            [&](const media::Media& m) {
                return typeid(m) == typeid(media) && m == media;
            }), vec.end());
    }
}

void MediaContainer::clear() {
    for (auto& vec : data_) {
        vec.clear();
    }
}

const std::vector<media::Media>& MediaContainer::getAll() const {
    return data_[INDEX_ALL];
}

const std::vector<media::Media>& MediaContainer::getByIndex(int idx) const {
    return data_[idx];
}

std::vector<const media::Media*> MediaContainer::getByGroupIndex(int idx) const {
    std::vector<const media::Media*> result;

    auto appendGroup = [&](int groupIndex) {
        for (const auto& media : data_[groupIndex]) {
            result.push_back(&media);
        }
    };

    switch (idx) {
        case INDEX_NOVEL:
            appendGroup(INDEX_NOVEL);
            appendGroup(INDEX_EBOOK);
            appendGroup(INDEX_AUDIOBOOK);
            break;
        case INDEX_MOVIE:
            appendGroup(INDEX_MOVIE);
            appendGroup(INDEX_SERIES);
            break;
        case INDEX_ALL:
            appendGroup(INDEX_ALL);
            break;
        default:
            appendGroup(idx);
            break;
    }

    return result;
}


std::vector<const media::Media*> MediaContainer::filter(const media::Media& media) const {
    std::vector<const media::Media*> results;
    for (const media::Media* m : getByGroupIndex(detectIndex(media))) {
        if (media.filter(*m)) {
            results.push_back(m);
        }
    }
    return results;
}

int MediaContainer::serialize(QSaveFile& file) const {
    return Serializer::Serialize(data_[INDEX_ALL], file);
}

} // namespace memory
