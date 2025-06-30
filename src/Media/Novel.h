#ifndef MEDIA_ROMANZO_H
#define MEDIA_ROMANZO_H

#include "Media.h"

namespace media {

class Novel : public Media {
 private:
  std::string author_;
  std::string publisher_;
  int pages_;
  std::string series_;
  std::string isbn_;

 public:
  explicit Novel(const std::string& title = "", int publicationYear = std::numeric_limits<int>::min(),
                 const std::string& language = "", bool favorite = false, const std::vector<std::string>& genres = {},
                 const std::string& imagePath = "", const std::string& notes = "", const std::string& author = "",
                 const std::string& publisher = "", int pages = std::numeric_limits<int>::min(),
                 const std::string& series = "", const std::string& isbn = "");
  explicit Novel(const Media&, const std::string& author = "", const std::string& publisher = "",
                 int pages = std::numeric_limits<int>::min(), const std::string& series = "",
                 const std::string& isbn = "");

  bool operator==(const Media&) const override;
  const std::string& getAuthor() const;
  const std::string& getPublisher() const;
  int getPages() const;
  const std::string& getSeries() const;
  const std::string& getIsbn() const;

  void setAuthor(const std::string& author);
  void setPublisher(const std::string& publisher);
  void setPages(int pages);
  void setSeries(const std::string& series);
  void setIsbn(const std::string& isbn);

  std::unique_ptr<Media> makePtr() const override;

  bool filter(const Media& input) const override;

  void accept(IConstMediaVisitor&) const override;
};

}  // namespace media
#endif  // MEDIA_ROMANZO_H
