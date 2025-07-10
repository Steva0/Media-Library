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
  friend class MediaTypeVisitor;

 public:
  enum class Type { All = 0, Novel, Album, Movie, Ebook, AudioBook, Series, TypeCount };

  static std::string typeToString(Type);
  static std::string typeToString(size_t);
  static const std::array<std::string, static_cast<size_t>(Type::TypeCount)> kTypeStrings;

 private:
  std::array<std::vector<std::unique_ptr<media::Media>>, static_cast<int>(Type::TypeCount)> data_;

  std::vector<const media::Media *> getByType(Type type) const;
  std::vector<const media::Media *> getByGroup(Type type) const;

  class MediaOpVisitor : public media::IConstMediaVisitor {
   public:
    enum class Operation { kAddMedia, kGetGroups };
   private:
    MediaContainer *container_;
    const MediaContainer *const_container_;
    Operation operation_;
    std::vector<const media::Media*> groups_;

    void appendGroup(Type);

   public:
    explicit MediaOpVisitor(MediaContainer *, Operation op = Operation::kAddMedia);
    explicit MediaOpVisitor(const MediaContainer *, Operation op = Operation::kGetGroups);

    void visit(const media::Media &) override;
    void visit(const media::Album &) override;
    void visit(const media::Movie &) override;
    void visit(const media::Series &) override;
    void visit(const media::Novel &) override;
    void visit(const media::AudioBook &) override;
    void visit(const media::Ebook &) override;

    std::vector<const media::Media *> getGroups() const { return groups_; }
  };

  void addMedia(const media::Album &);
  void addMedia(const media::Novel &);
  void addMedia(const media::AudioBook &);
  void addMedia(const media::Ebook &);
  void addMedia(const media::Movie &);
  void addMedia(const media::Series &);

 public:
  void addMedia(const media::Media &);

  void removeMedia(const media::Media &media);
  void clear();

  std::vector<const media::Media *> filter(const media::Media &media) const;
  std::vector<const media::Media *> getAll() const;

  int serialize(QFile &file) const;
};

}  // namespace memory

#endif  // MEMORY_MEDIACONTAINER_H
