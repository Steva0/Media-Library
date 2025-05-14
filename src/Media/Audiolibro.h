#ifndef Audiolibro_H
#define Audiolibro_H

#include "Romanzo.h"

namespace media {

class Audiolibro : public Romanzo {
private:
    std::string narrator_;
    std::string streamingService_;

public:
    Audiolibro(const std::string& title, int publicationYear, const std::string& language,
              bool favorite, const std::vector<std::string>& genres, const std::string& imagePath, const std::string& notes,
              const std::string& author, const std::string& publisher,
              unsigned int duration, const std::string& series, const std::string& isbn,
              const std::string& narrator, const std::string& streamingService);

    Audiolibro(const Audiolibro& other);
    Audiolibro& operator=(const Audiolibro& other);

    void accept(IConstMediaVisitor& v) const override;

    std::string getNarrator() const;
    std::string getStreamingService() const;

    void setNarrator(const std::string& narrator);
    void setStreamingService(const std::string& service);
};

}

#endif // Audiolibro_H