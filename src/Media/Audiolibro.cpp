#include "Audiolibro.h"

namespace media {

Audiolibro::Audiolibro(const std::string& title, int publicationYear, const std::string& language,
                     bool favorite, const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
                     const std::string& author, const std::string& publisher,
                     unsigned int duration, const std::string& series, const std::string& isbn,
                     const std::string& narrator, const std::string& streamingService)
    : Romanzo(title, publicationYear, language, favorite, genres, imagePath, notes,
            author, publisher, duration, series, isbn),
      narrator_(narrator), streamingService_(streamingService) {}

Audiolibro::Audiolibro(const Audiolibro& other)
    : Romanzo(other),
      narrator_(other.narrator_),
      streamingService_(other.streamingService_) {}

Audiolibro& Audiolibro::operator=(const Audiolibro& other) {
    if (this != &other) {
        Romanzo::operator=(other);
        narrator_ = other.narrator_;
        streamingService_ = other.streamingService_;
    }
    return *this;
}

void Audiolibro::accept(IMediaVisitor& v) const {
    v.visit(*this);
}

std::string Audiolibro::getNarrator() const {
    return narrator_;
}

std::string Audiolibro::getStreamingService() const {
    return streamingService_;
}

void Audiolibro::setNarrator(const std::string& narrator) {
    narrator_ = narrator;
}

void Audiolibro::setStreamingService(const std::string& service) {
    streamingService_ = service;
}

}