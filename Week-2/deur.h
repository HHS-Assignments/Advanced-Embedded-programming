#ifndef DEUR_H
#define DEUR_H

#include <utility>

class QPaintDevice;

class Deur
{
public:
    Deur(int x, int y, unsigned int lengte);
    virtual ~Deur() = default;

    virtual void teken(QPaintDevice *device) = 0;

    bool isOpen() const;
    unsigned int deurLengte() const;
    std::pair<int, int> coordinaten() const;

protected:
    void zetOpen(bool open);

    int x_coordinat;
    int y_coordinat;
    unsigned int lengte;
    bool open;
};

#endif // DEUR_H