#include "AudioBook.h"

namespace media {

AudioBook::AudioBook(const std::string& title, int publicationYear, const std::string& language, bool favorite,
                     const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
                     const std::string& author, const std::string& publisher, int duration, const std::string& series,
                     const std::string& isbn, const std::string& narrator, const std::string& streamingService)
    : Novel(title, publicationYear, language, favorite, genres, imagePath, notes, author, publisher, duration, series,
            isbn),
      narrator_(narrator),
      streamingService_(streamingService) {}
AudioBook::AudioBook(const Novel& novel, const std::string& narrator, const std::string& streamingService)
    : Novel(novel), narrator_(narrator), streamingService_(streamingService) {}

bool AudioBook::operator==(const Media& other) const {
  const auto* other_audio_book = dynamic_cast<const AudioBook*>(&other);
  if (other_audio_book) {
    return Novel::operator==(*other_audio_book) && narrator_ == other_audio_book->narrator_ &&
           streamingService_ == other_audio_book->streamingService_;
  }
  return false;
}

std::unique_ptr<Media> AudioBook::makePtr() const { return std::make_unique<AudioBook>(*this); }
std::string AudioBook::displayType() const { return "AUDIOLIBRO"; }

const std::string& AudioBook::getNarrator() const { return narrator_; }

const std::string& AudioBook::getStreamingService() const { return streamingService_; }

int AudioBook::getDuration() const { return getPages(); }

void AudioBook::setNarrator(const std::string& narrator) { narrator_ = narrator; }

void AudioBook::setStreamingService(const std::string& service) { streamingService_ = service; }

void AudioBook::setDuration(int duration) { setPages(duration); }

bool AudioBook::filter(const Media& input) const {
  if (!Novel::filter(input)) return false;
  const AudioBook* audiobookPtr = dynamic_cast<const AudioBook*>(&input);
  if (!audiobookPtr) return false;  // Protegge da cast fallito

  // Filtro specifico AudioBook
  if (!narrator_.empty() && !stringContainsIgnoreCase(audiobookPtr->getNarrator(), narrator_)) return false;

  if (!streamingService_.empty() && !stringContainsIgnoreCase(audiobookPtr->getStreamingService(), streamingService_))
    return false;

  return true;
}

void AudioBook::accept(IConstMediaVisitor& v) const { v.visit(*this); }

}  // namespace media
