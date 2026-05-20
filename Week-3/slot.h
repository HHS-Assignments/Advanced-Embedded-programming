#ifndef SLOT_H
#define SLOT_H

#include <string>

class Slot
{
public:
    virtual ~Slot() = default;

    virtual void vergrendel() = 0;
    virtual bool ontgrendel(const std::string &waarde) = 0;
    virtual bool isVergrendeld() const = 0;
};

#endif // SLOT_H