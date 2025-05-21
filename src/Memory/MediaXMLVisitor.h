#ifndef MEMORY_XML_VISITOR_H
#define MEMORY_XML_VISITOR_H
#include <QDomElement>

#include "../Media/IConstMediaVisitor.h"

namespace memory {
class MediaXMLVisitor : public media::IConstMediaVisitor {
 private:
  QDomElement element_;

 public:
  QDomElement &get() const;

  void visit(const media::Media &) override;
  void visit(const media::Album &) override;
  void visit(const media::Movie &) override;
  void visit(const media::Series &) override;
  void visit(const media::Novel &) override;
  void visit(const media::AudioBook &) override;
  void visit(const media::Ebook &) override;
};
}  // namespace memory
#endif
