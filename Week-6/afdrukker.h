#ifndef AFDRUKKER_H
#define AFDRUKKER_H

#include <string>

class Afdrukker
{
public:
    virtual ~Afdrukker() = default;
    virtual void druk(const std::string &tekst) = 0;
};

#endif // AFDRUKKER_H
