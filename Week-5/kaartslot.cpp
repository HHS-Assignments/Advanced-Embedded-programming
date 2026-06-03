#include "kaartslot.h"
#include "idkaart.h"

#include <algorithm>

std::map<std::string, std::shared_ptr<IdKaart>> KaartSlot::idKaarten;

KaartSlot::KaartSlot(std::string plaats)
    : plaats(std::move(plaats)), vergrendeld(true)
{
}

void KaartSlot::vergrendel()
{
    vergrendeld = true;
}

bool KaartSlot::ontgrendel(const std::string &waarde)
{
    // waarde is expected to be the unique id string
    if (auto it = idKaarten.find(waarde); it != idKaarten.end()) {
        if (it->second && it->second->heeftToegang(this)) {
            vergrendeld = false;
            return true;
        }
    }
    return false;
}

bool KaartSlot::isVergrendeld() const
{
    return vergrendeld;
}

void KaartSlot::voegIdKaartToe(std::shared_ptr<IdKaart> idKaart)
{
    if (!idKaart) return;
    idKaarten[idKaart->getId()] = std::move(idKaart);
}

void KaartSlot::verwijderIdKaart(const std::string &id)
{
    idKaarten.erase(id);
}

std::shared_ptr<IdKaart> KaartSlot::getIdKaart(const std::string &id)
{
    auto it = idKaarten.find(id);
    if (it == idKaarten.end()) return {};
    return it->second;
}
