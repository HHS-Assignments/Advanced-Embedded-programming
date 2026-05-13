#include "sleutelslot.h"

#include <utility>

SleutelSlot::SleutelSlot(std::string sleutel)
    : sleutel(std::move(sleutel)), vergrendeld(true)
{
}

void SleutelSlot::vergrendel()
{
    vergrendeld = true;
}

bool SleutelSlot::ontgrendel(const std::string &waarde)
{
    if (waarde != sleutel) {
        return false;
    }

    vergrendeld = false;
    return true;
}

bool SleutelSlot::isVergrendeld() const
{
    return vergrendeld;
}