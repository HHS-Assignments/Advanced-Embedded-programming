#ifndef IDKAART_H
#define IDKAART_H

#include <string>
#include <vector>

class KaartSlot;

class IdKaart
{
public:
    IdKaart(std::string id, std::string naam, std::string adres);

    const std::string &getId() const;
    const std::string &getNaam() const;
    const std::string &getAdres() const;

    void geefToegang(KaartSlot *slot);
    void verwijderToegang(KaartSlot *slot);
    bool heeftToegang(KaartSlot *slot) const;

private:
    std::string m_id;
    std::string m_naam;
    std::string m_adres;
    std::vector<KaartSlot*> m_toegang;
};

#endif // IDKAART_H
