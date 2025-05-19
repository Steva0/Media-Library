#ifndef AudioBook_H
#define AudioBook_H

#include "Novel.h"

namespace media {

class AudioBook : public Novel {
private:
    std::string narrator_;
    std::string streamingService_;

public:
    AudioBook(const std::string& title, int publicationYear, const std::string& language,
              bool favorite, const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
              const std::string& author, const std::string& publisher,
              unsigned int duration, const std::string& series, const std::string& isbn,
              const std::string& narrator, const std::string& streamingService);

    void accept(IConstMediaVisitor& v) const override;

    std::string getNarrator() const;
    std::string getStreamingService() const;

    void setNarrator(const std::string& narrator);
    void setStreamingService(const std::string& service);
};

}

#endif // AudioBook_H