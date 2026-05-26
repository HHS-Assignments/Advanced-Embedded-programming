#include "herkenningsslot.h"

#include <sstream>

HerkenningsSlot::HerkenningsSlot()
    : vergrendeldFlag(true)
{
}

void HerkenningsSlot::vergrendel()
{
    vergrendeldFlag = true;
}

bool HerkenningsSlot::ontgrendel(const std::string &waarde)
{
    auto it = kaartenbak.find(waarde);
    if (it == kaartenbak.end()) {
        return false;
    }

    if (!it->second) {
        return false;
    }

    vergrendeldFlag = false;
    return true;
}

bool HerkenningsSlot::isVergrendeld() const
{
    return vergrendeldFlag;
}

void HerkenningsSlot::voegAutorisatieToe(const std::string &naam, bool toegang)
{
    kaartenbak[naam] = toegang;
}

void HerkenningsSlot::setAfdrukker(std::shared_ptr<Afdrukker> afdrukker)
{
    this->afdrukker = std::move(afdrukker);
}

void HerkenningsSlot::drukKaartenbak() const
{
    if (!afdrukker) return;

    std::ostringstream oss;
    for (const auto &p : kaartenbak) {
        oss << p.first << " : " << (p.second ? "TOEGESTAAN" : "GEWEIGERD") << "\n";
    }

    afdrukker->druk(oss.str());
}
