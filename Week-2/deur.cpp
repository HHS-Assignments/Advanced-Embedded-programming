#include "deur.h"

#include "deurdefs.h"
#include "slot.h"

Deur::Deur(int x, int y, unsigned int lengte)
    : x_coordinat(x), y_coordinat(y), lengte(lengte), open(DICHT), slot(nullptr)
{
}

bool Deur::isOpen() const
{
    return open;
}

unsigned int Deur::deurLengte() const
{
    return lengte;
}

std::pair<int, int> Deur::coordinaten() const
{
    return {x_coordinat, y_coordinat};
}

void Deur::zetOpen(bool open)
{
    this->open = open;
}

void Deur::zetSlot(Slot *slot)
{
    this->slot = slot;
}

bool Deur::slotOntgrendeld() const
{
    return !slot || !slot->isVergrendeld();
}

void Deur::vergrendelSlot()
{
    if (slot) {
        slot->vergrendel();
    }
}