#ifndef MEMORY_MEDIACONTAINER_H
#define MEMORY_MEDIACONTAINER_H

#include <QFile>
#include <array>
#include <memory>
#include <vector>

#include "../Media/Album.h"
#include "../Media/AudioBook.h"
#include "../Media/Ebook.h"
#include "../Media/Media.h"
#include "../Media/Movie.h"
#include "../Media/Novel.h"
#include "../Media/Series.h"
#include "Serializer.h"

namespace memory {

class MediaContainer {
 public:
  enum class Type {
    All = 0,
    Novel,
    Album,
    Movie,
    Ebook,
    AudioBook,
    Series,
    TypeCount
  };


  static std::string typeToString(Type);

 private:
  // per assicurare una a compile time una corrispondenza 1 a 1 tra stringhe e valori enum
  static constexpr std::array<std::string_view, static_cast<size_t>(Type::TypeCount)> typeStrings();

  std::array<std::vector<std::unique_ptr<media::Media>>,
             static_cast<int>(Type::TypeCount)>
      data_;

  Type detectType(const media::Media& media) const;
  std::vector<const media::Media*> getByType(Type type) const;
  std::vector<const media::Media*> getByGroup(Type type) const;

 public:
  void addMedia(const media::Media& media);
  void addMedia(const std::vector<media::Media>& listaMedia);
  void removeMedia(const media::Media& media);
  void clear();

  std::vector<const media::Media*> filter(const media::Media& media) const;
  std::vector<const media::Media*> getAll() const;

  int serialize(QFile& file) const;
};

}  // namespace memory

#endif  // MEMORY_MEDIACONTAINER_H
