#ifndef MEDIA_IMedia_H
#define MEDIA_IMedia_H

#include "../Memory/MediaJSONVisitor.h"
#include "../Memory/MediaXMLVisitor.h"
#include "IConstMediaVisitor.h"

namespace media {

class IMedia {
 public:
  virtual void accept(IConstMediaVisitor &) const = 0;
  virtual bool open() = 0;
  virtual std::unique_ptr<Media> makePtr() const = 0;
  virtual ~IMedia() = default;
  virtual std::string displayType() const = 0;
};

}  // namespace media

#endif
