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

}