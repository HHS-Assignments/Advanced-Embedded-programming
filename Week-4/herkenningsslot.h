#ifndef HERKENNINGSSLOT_H
#define HERKENNINGSSLOT_H

#include "slot.h"
#include "afdrukker.h"

#include <map>
#include <memory>
#include <string>

class HerkenningsSlot : public Slot
{
public:
    HerkenningsSlot();

    void vergrendel() override;
    bool ontgrendel(const std::string &waarde) override;
    bool isVergrendeld() const override;

    void voegAutorisatieToe(const std::string &naam, bool toegang);
    void setAfdrukker(std::shared_ptr<Afdrukker> afdrukker);
    void drukKaartenbak() const;

private:
    std::map<std::string, bool> kaartenbak;
    bool vergrendeldFlag;
    std::shared_ptr<Afdrukker> afdrukker;
};

#endif // HERKENNINGSSLOT_H
ko