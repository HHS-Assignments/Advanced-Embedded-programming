#include "idkaart.h"
#include "kaartslot.h"

#include <algorithm>

IdKaart::IdKaart(std::string id, std::string naam, std::string adres)
    : m_id(std::move(id)), m_naam(std::move(naam)), m_adres(std::move(adres))
{
}

const std::string &IdKaart::getId() const { return m_id; }
const std::string &IdKaart::getNaam() const { return m_naam; }
const std::string &IdKaart::getAdres() const { return m_adres; }

void IdKaart::geefToegang(KaartSlot *slot)
{
    if (!slot) return;
    if (std::find(m_toegang.begin(), m_toegang.end(), slot) == m_toegang.end()) {
        m_toegang.push_back(slot);
    }
}

void IdKaart::verwijderToegang(KaartSlot *slot)
{
    if (!slot) return;
    auto it = std::remove(m_toegang.begin(), m_toegang.end(), slot);
    m_toegang.erase(it, m_toegang.end());
}

bool IdKaart::heeftToegang(KaartSlot *slot) const
{
    if (!slot) return false;
    return std::find(m_toegang.begin(), m_toegang.end(), slot) != m_toegang.end();
}
