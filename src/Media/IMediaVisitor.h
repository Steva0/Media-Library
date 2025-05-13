#ifndef MEDIA_I_MEDIA_VISITOR_H
#define MEDIA_I_MEDIA_VISITOR_H
class Album;
class Movie;
class Series;

namespace media {
class IMediaVisitor {
 public:
  virtual void visit(const Album &) = 0;
  virtual void visit(const Movie &) = 0;
  virtual void visit(const Series &) = 0;
};
}  // namespace library::media
#endif
