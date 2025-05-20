#ifndef MEDIA_MEDIA_H
#define MEDIA_MEDIA_H
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <limits>

#include "IMedia.h"
#include "IConstMediaVisitor.h"
#include "StringUtils.h"

namespace media {
class Media : IMedia{
 private:
  std::string title_;
  int release_;
  std::string language_;
  bool favourite_;
  std::vector<std::string> genres_;
  std::string img_path_;
  std::string notes_;

  protected:
  Media(const std::string &title = "", int release = std::numeric_limits<int>::min(), const std::string &language = "",
        bool favourite = false, const std::vector<std::string> &genres = {},
        const std::string &img_path = "", const std::string &notes = "");
  
 public:

  virtual bool operator==(const Media &other) const;
  
  void accept(IConstMediaVisitor &) const override;
  bool open() override;

  // Possiamo scegliere noi se utilizzare un riferimento costante o fare una copia
  // Potenziali problemi possono verosimilmente essere la vita delle variabili
  // Ignoro potenziali problemi di incapsulamento dovuti al const_cast
  const std::string &getTitle() const;
  int getRelease() const;
  const std::string &getLanguage() const;
  bool isFavourite() const;
  const std::vector<std::string> &getGenres() const;
  const std::string &getImgPath() const;
  const std::string &getNotes() const;

  virtual std::vector<std::shared_ptr<Media>> filter(const std::vector<std::shared_ptr<Media>> &media) const;
}; 
}  // namespace media
#endif
