#include "schuifdeur.h"

#include "deurdefs.h"
#include "sensor.h"

#include <QPainter>
#include <QPen>
#include <utility>

Schuifdeur::Schuifdeur(int x, int y, unsigned int lengte, std::shared_ptr<Sensor> sensor)
    : Deur(x, y, lengte), sensor(std::move(sensor))
{
}

bool Schuifdeur::openen()
{
    if (!slotOntgrendeld()) {
        return false;
    }

    zetOpen(OPEN);
    return true;
}

bool Schuifdeur::sluiten()
{
    if (sensor && sensor->isGeactiveerd()) {
        return false;
    }

    zetOpen(DICHT);
    vergrendelSlot();
    return true;
}

void Schuifdeur::teken(QPaintDevice *device)
{
    QPainter painter(device);
    QPen pen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    constexpr int afbeeldingsOffset = 10;

    const int verschuiving = static_cast<int>(lengte);
    const int tekeningY = isOpen() ? y_coordinat + verschuiving : y_coordinat;
    painter.drawLine(x_coordinat + afbeeldingsOffset, tekeningY + afbeeldingsOffset, x_coordinat + afbeeldingsOffset, tekeningY + afbeeldingsOffset + static_cast<int>(lengte));
}