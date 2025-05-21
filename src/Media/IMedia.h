#ifndef MEDIA_IMedia_H
#define MEDIA_IMedia_H

#include "IConstMediaVisitor.h"

namespace media {

class IMedia {
    virtual void accept(IConstMediaVisitor &) const = 0;
    virtual bool open() = 0;
    virtual std::unique_ptr<Media> clone() const = 0;
};

}

#endif