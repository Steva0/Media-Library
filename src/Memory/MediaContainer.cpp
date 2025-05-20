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

const std::vector<media::Media>& MediaContainer::getByIndex(int idx) const {
    return data_[idx];
}

std::vector<const media::Media*> MediaContainer::getByGroupIndex(int idx) const {
    std::vector<const media::Media*> result;

    switch (idx) {
        case INDEX_NOVEL:
            result.insert(result.end(), data_[INDEX_NOVEL].begin(), data_[INDEX_NOVEL].end());
            result.insert(result.end(), data_[INDEX_EBOOK].begin(), data_[INDEX_EBOOK].end());
            result.insert(result.end(), data_[INDEX_AUDIOBOOK].begin(), data_[INDEX_AUDIOBOOK].end());
            break;
        case INDEX_MOVIE:
            result.insert(result.end(), data_[INDEX_MOVIE].begin(), data_[INDEX_MOVIE].end());
            result.insert(result.end(), data_[INDEX_SERIES].begin(), data_[INDEX_SERIES].end());
            break;
        case INDEX_ALL:
            result.insert(result.end(), data_[INDEX_ALL].begin(), data_[INDEX_ALL].end());
            break;
        default:
            result.insert(result.end(), data_[idx].begin(), data_[idx].end());
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
