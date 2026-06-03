#ifndef DEUR_H
#define DEUR_H

#include <utility>
#include <list>
#include <memory>

class QPaintDevice;
class Slot;

class Deur
{
public:
    Deur(int x, int y, unsigned int lengte);
    virtual ~Deur() = default;

    virtual void teken(QPaintDevice *device) = 0;

    bool isOpen() const;
    unsigned int deurLengte() const;
    std::pair<int, int> coordinaten() const;
    void zetSlot(std::shared_ptr<Slot> slot);
    void voegSlotToe(std::shared_ptr<Slot> slot);

protected:
    void zetOpen(bool open);
    bool slotOntgrendeld() const;
    void vergrendelSlot();

    int x_coordinat;
    int y_coordinat;
    unsigned int lengte;
    bool open;
    std::list<std::shared_ptr<Slot>> m_slots;
};

#endif // DEUR_H