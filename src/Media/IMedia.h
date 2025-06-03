#ifndef MEDIA_IMedia_H
#define MEDIA_IMedia_H

#include "IConstMediaVisitor.h"
#include "../Memory/MediaJSONVisitor.h"
#include "../Memory/MediaXMLVisitor.h"

namespace media {

class IMedia {
    virtual void accept(IConstMediaVisitor &) const = 0;
    virtual bool open() = 0;
    virtual std::unique_ptr<Media> makePtr() const = 0;
};

}

#endif