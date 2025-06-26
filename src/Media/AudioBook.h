#ifndef MEDIA_AUDIOBOOK_H
#define MEDIA_AUDIOBOOK_H

#include "Novel.h"

namespace media {

class AudioBook : public Novel {
 private:
  std::string narrator_;
  std::string streamingService_;

 public:
  // durata è in minuti e usa il campo dati pagine di Novel
  explicit AudioBook(const std::string& title, int publicationYear = std::numeric_limits<int>::min(),
                     const std::string& language = "", bool favorite = false,
                     const std::vector<std::string>& genres = {}, const std::string& imagePath = "",
                     const std::string& notes = "", const std::string& author = "", const std::string& publisher = "",
                     int pages = std::numeric_limits<int>::min(), const std::string& series = "",
                     const std::string& isbn = "", const std::string& narrator = "",
                     const std::string& streamingService = "");

  bool operator==(const Media &) const override;
  const std::string& getNarrator() const;
  const std::string& getStreamingService() const;

  void setNarrator(const std::string& narrator);
  void setStreamingService(const std::string& service);

  std::unique_ptr<Media> makePtr() const override;

  bool filter(const Media& input) const override;

  void accept(IConstMediaVisitor&) const override;
};

}  // namespace media

#endif  // MEDIA_AUDIOBOOK_H
