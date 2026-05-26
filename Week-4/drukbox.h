#ifndef DRUKBOX_H
#define DRUKBOX_H

#include "afdrukker.h"

#include <memory>

class QTextBrowser;

class Drukbox : public Afdrukker
{
public:
    explicit Drukbox(QTextBrowser *browser);

    void druk(const std::string &tekst) override;

private:
    QTextBrowser *browser;
};

#endif // DRUKBOX_H
