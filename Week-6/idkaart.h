#ifndef IDKAART_H
#define IDKAART_H

#include <string>
#include <vector>

class KaartSlot;

class IdKaart
{
public:
    IdKaart(std::string id, std::string naam, std::string adres);
    virtual ~IdKaart() = default;

    virtual const std::string &getId() const;
    virtual const std::string &getNaam() const;
    virtual const std::string &getAdres() const;

    virtual void geefToegang(KaartSlot *slot);
    virtual void verwijderToegang(KaartSlot *slot);
    virtual bool heeftToegang(KaartSlot *slot) const;

private:
    std::string m_id;
    std::string m_naam;
    std::string m_adres;
    std::vector<KaartSlot*> m_toegang;
};

#endif // IDKAART_H
