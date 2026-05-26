#include "draaideur.h"

#include "deurdefs.h"

#include <QPainter>
#include <QPen>

Draaideur::Draaideur(int x, int y, unsigned int lengte, bool linksom)
    : Deur(x, y, lengte), linksom(linksom)
{
}

bool Draaideur::openen()
{
    if (!slotOntgrendeld()) {
        return false;
    }

    zetOpen(OPEN);
    return true;
}

bool Draaideur::sluiten()
{
    zetOpen(DICHT);
    vergrendelSlot();
    return true;
}

void Draaideur::teken(QPaintDevice *device)
{
    QPainter painter(device);
    QPen pen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    constexpr int afbeeldingsOffset = 10;

    const int lengteInt = static_cast<int>(lengte);
    int eindX = x_coordinat;
    int eindY = y_coordinat + lengteInt;

    if (isOpen()) {
        if (linksom) {
            eindX = x_coordinat - lengteInt;
            eindY = y_coordinat;
        } else {
            eindX = x_coordinat + lengteInt;
            eindY = y_coordinat;
        }
    }

    painter.drawLine(x_coordinat + afbeeldingsOffset, y_coordinat + afbeeldingsOffset, eindX + afbeeldingsOffset, eindY + afbeeldingsOffset);
}