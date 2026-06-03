#include "deur.h"

#include "deurdefs.h"
#include "slot.h"

#include <algorithm>

Deur::Deur(int x, int y, unsigned int lengte)
    : x_coordinat(x), y_coordinat(y), lengte(lengte), open(DICHT)
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

void Deur::zetSlot(std::shared_ptr<Slot> slot)
{
    m_slots.clear();
    if (slot) {
        m_slots.push_back(std::move(slot));
    }
}

void Deur::voegSlotToe(std::shared_ptr<Slot> slot)
{
    if (slot) {
        m_slots.push_back(std::move(slot));
    }
}

bool Deur::slotOntgrendeld() const
{
    // If there are no m_slots the door is considered unlocked
    if (m_slots.empty()) {
        return true;
    }
    // Door is unlocked only when ALL m_slots are unlocked
    return std::all_of(m_slots.begin(), m_slots.end(), [](const std::shared_ptr<Slot> &s){
        return s && !s->isVergrendeld();
    });
}

void Deur::vergrendelSlot()
{
    for (auto &s : m_slots) {
        if (s) {
            s->vergrendel();
        }
    }
}