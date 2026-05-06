#include "deur.h"

#include "deurdefs.h"

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