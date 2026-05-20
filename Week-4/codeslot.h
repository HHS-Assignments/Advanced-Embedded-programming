#ifndef CODESLOT_H
#define CODESLOT_H

#include "slot.h"

class CodeSlot : public Slot
{
public:
    explicit CodeSlot(int code);

    void vergrendel() override;
    bool ontgrendel(const std::string &waarde) override;
    bool isVergrendeld() const override;

private:
    int code;
    bool vergrendeld;
};

#endif // CODESLOT_H