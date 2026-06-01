#ifndef KAARTSLOT_H
#define KAARTSLOT_H

#include "slot.h"

#include <map>
#include <memory>
#include <string>

class IdKaart;

class KaartSlot : public Slot
{
public:
    explicit KaartSlot(std::string plaats);

    void vergrendel() override;
    bool ontgrendel(const std::string &waarde) override;
    bool isVergrendeld() const override;

    static void voegIdKaartToe(std::shared_ptr<IdKaart> idKaart);
    static void verwijderIdKaart(const std::string &id);
    static std::shared_ptr<IdKaart> getIdKaart(const std::string &id);

private:
    std::string plaats;
    bool vergrendeld;

    static std::map<std::string, std::shared_ptr<IdKaart>> idKaarten;
};

#endif // KAARTSLOT_H
