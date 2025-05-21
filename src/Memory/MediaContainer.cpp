#include "MediaContainer.h"
#include <typeinfo>
#include <algorithm>

namespace memory {

void MediaContainer::addMedia(const media::Media& media) {
    data_[static_cast<size_t>(Type::All)].push_back(media);

    Type t = detectType(media);
    if (t != Type::All) {
        data_[static_cast<size_t>(t)].push_back(media);
    }
}

MediaContainer::Type MediaContainer::detectType(const media::Media& media) const {
    if (dynamic_cast<const media::Series*>(&media)) {
        return Type::Series;
    }
    if (dynamic_cast<const media::AudioBook*>(&media)) {
        return Type::AudioBook;
    }
    if (dynamic_cast<const media::Ebook*>(&media)) {
        return Type::Ebook;
    }
    if (dynamic_cast<const media::Movie*>(&media)) {
        return Type::Movie;
    }
    if (dynamic_cast<const media::Album*>(&media)) {
        return Type::Album;
    }
    if (dynamic_cast<const media::Novel*>(&media)) {
        return Type::Novel;
    }
    return Type::All;
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
    return data_[static_cast<int>(Type::All)];
}

std::vector<const media::Media*> MediaContainer::getByType(Type type) const {
    std::vector<const media::Media*> result;
    for (const auto& media : data_[static_cast<int>(type)]) {
        result.push_back(&media);
    }
    return result;
}


std::vector<const media::Media*> MediaContainer::getByGroup(Type type) const {
    std::vector<const media::Media*> result;

    auto appendGroup = [&](Type t) {
        for (const auto& media : data_[static_cast<int>(t)]) {
            result.push_back(&media);
        }
    };

    switch (type) {
    case Type::Novel:
        appendGroup(Type::Novel);
        appendGroup(Type::Ebook);
        appendGroup(Type::AudioBook);
        break;

    case Type::Movie:
        appendGroup(Type::Movie);
        appendGroup(Type::Series);
        break;

    case Type::All:
        appendGroup(Type::All);
        break;

    default:
        appendGroup(type);
        break;
    }

    return result;
}

std::vector<const media::Media*> MediaContainer::filter(const media::Media& media) const {
    std::vector<const media::Media*> results;
    Type t = detectType(media);
    for (const media::Media* m : getByGroup(t)) {
        if (media.filter(*m)) {
            results.push_back(m);
        }
    }
    return results;
}

int MediaContainer::serialize(QSaveFile& file) const {
    return Serializer::Serialize(data_[static_cast<size_t>(Type::All)], file);
}

} // namespace memory
