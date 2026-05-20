#ifndef SCHUIFDEUR_H
#define SCHUIFDEUR_H

#include "deur.h"

#include <memory>

class Sensor;

class Schuifdeur : public Deur
{
public:
    Schuifdeur(int x, int y, unsigned int lengte, std::shared_ptr<Sensor> sensor);

    void teken(QPaintDevice *device) override;

    bool openen();
    bool sluiten();

private:
    std::shared_ptr<Sensor> sensor;
};

#endif // SCHUIFDEUR_H