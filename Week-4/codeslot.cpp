#include "codeslot.h"

#include <exception>
#include <string>

CodeSlot::CodeSlot(int code)
    : code(code), vergrendeld(true)
{
}

void CodeSlot::vergrendel()
{
    vergrendeld = true;
}

bool CodeSlot::ontgrendel(const std::string &waarde)
{
    try {
        if (std::stoi(waarde) != code) {
            return false;
        }
    } catch (const std::exception &) {
        return false;
    }

    vergrendeld = false;
    return true;
}

bool CodeSlot::isVergrendeld() const
{
    return vergrendeld;
}