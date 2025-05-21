#ifndef MEDIA_AUDIOBOOK_H
#define MEDIA_AUDIOBOOK_H

#include "Media/IConstMediaVisitor.h"
#include "Novel.h"

namespace media {

class AudioBook : public Novel {
private:
    std::string narrator_;
    std::string streamingService_;

public:
    //durata è in minuti e usa il campo dati pagine di Novel
    AudioBook(const std::string& title, int publicationYear, const std::string& language,
              bool favorite, const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
              const std::string& author, const std::string& publisher,
              unsigned int duration, const std::string& series, const std::string& isbn,
              const std::string& narrator = "", const std::string& streamingService = "");

    bool operator==(const Media& other) const override;

    std::string getNarrator() const;
    std::string getStreamingService() const;

    void setNarrator(const std::string& narrator);
    void setStreamingService(const std::string& service);

    std::unique_ptr<Media> clone() const override;

    bool filter(const Media& audiobook) const override;

    void accept(IConstMediaVisitor &) const override;
};

}

#endif // MEDIA_AUDIOBOOK_H
