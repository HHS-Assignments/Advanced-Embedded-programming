#include "drukbox.h"

#include <QTextBrowser>

Drukbox::Drukbox(QTextBrowser *browser)
    : browser(browser)
{
}

void Drukbox::druk(const std::string &tekst)
{
    if (browser) {
        browser->setPlainText(QString::fromStdString(tekst));
    }
}
