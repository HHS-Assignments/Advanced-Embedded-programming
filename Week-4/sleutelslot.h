#ifndef SLEUTELSLOT_H
#define SLEUTELSLOT_H

#include "slot.h"

#include <string>

class SleutelSlot : public Slot
{
public:
    explicit SleutelSlot(std::string sleutel);

    void vergrendel() override;
    bool ontgrendel(const std::string &waarde) override;
    bool isVergrendeld() const override;

private:
    std::string sleutel;
    bool vergrendeld;
};

#endif // SLEUTELSLOT_H