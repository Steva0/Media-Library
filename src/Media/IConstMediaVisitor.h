#ifndef MEDIA_I_MEDIA_VISITOR_H
#define MEDIA_I_MEDIA_VISITOR_H

namespace media {

class Media;
class Album;
class Movie;
class Series;
class Novel;
class AudioBook;
class Ebook;

class IConstMediaVisitor {

 public:
  virtual void visit(const Media &) = 0;
  virtual void visit(const Album &) = 0;
  virtual void visit(const Movie &) = 0;
  virtual void visit(const Series &) = 0;
  virtual void visit(const Novel &) = 0;
  virtual void visit(const AudioBook &) = 0;
  virtual void visit(const Ebook &) = 0;
};

}  // namespace media
#endif

