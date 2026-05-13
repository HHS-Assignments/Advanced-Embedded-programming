#ifndef DEUR_H
#define DEUR_H

#include <utility>

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
    void zetSlot(Slot *slot);

protected:
    void zetOpen(bool open);
    bool slotOntgrendeld() const;
    void vergrendelSlot();

    int x_coordinat;
    int y_coordinat;
    unsigned int lengte;
    bool open;
    Slot *slot;
};

#endif // DEUR_H