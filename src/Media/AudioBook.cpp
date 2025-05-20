#include "AudioBook.h"

namespace media {

AudioBook::AudioBook(const std::string& title, int publicationYear, const std::string& language,
                     bool favorite, const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
                     const std::string& author, const std::string& publisher,
                     unsigned int duration, const std::string& series, const std::string& isbn,
                     const std::string& narrator, const std::string& streamingService)
    : Novel(title, publicationYear, language, favorite, genres, imagePath, notes,
            author, publisher, duration, series, isbn),
      narrator_(narrator), streamingService_(streamingService) {}


bool AudioBook::operator==(const Media& other) const {
    const AudioBook* otherAudioBook = dynamic_cast<const AudioBook*>(&other);
    if (otherAudioBook) {
        return Novel::operator==(*otherAudioBook) && narrator_ == otherAudioBook->narrator_ &&
               streamingService_ == otherAudioBook->streamingService_;
    }
    return false;
}

std::string AudioBook::getNarrator() const {
    return narrator_;
}

std::string AudioBook::getStreamingService() const {
    return streamingService_;
}

void AudioBook::setNarrator(const std::string& narrator) {
    narrator_ = narrator;
}

void AudioBook::setStreamingService(const std::string& service) {
    streamingService_ = service;
}

std::vector<std::shared_ptr<Media>> AudioBook::filter(const std::vector<std::shared_ptr<AudioBook>>& input) const {
    std::vector<std::shared_ptr<Media>> result;

    // Riutilizza filtro base di Novel (che include filtro di Media)
    std::vector<std::shared_ptr<Novel>> novels(input.begin(), input.end());
    std::vector<std::shared_ptr<Media>> filteredNovels = Novel::filter(novels);

    // Filtro specifico AudioBook
    for (const auto& novelPtr : filteredNovels) {
        auto audiobookPtr = std::dynamic_pointer_cast<AudioBook>(novelPtr);
        if (!audiobookPtr) continue;

        bool match = true;

        // File size
        if (narrator_ != "" && audiobookPtr->getNarrator()!= narrator_)
            match = false;

        // DRM
        if (streamingService_ != "" && audiobookPtr->getStreamingService() != streamingService_)
            match = false;

        if (match)
            result.push_back(audiobookPtr);
    }

    return result;
}

}