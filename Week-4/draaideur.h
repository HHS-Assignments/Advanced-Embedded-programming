#ifndef DRAAIDEUR_H
#define DRAAIDEUR_H

#include "deur.h"

class Draaideur : public Deur
{
public:
    Draaideur(int x, int y, unsigned int lengte, bool linksom);

    void teken(QPaintDevice *device) override;

    bool openen();
    bool sluiten();

private:
    bool linksom;
};

#endif // DRAAIDEUR_H