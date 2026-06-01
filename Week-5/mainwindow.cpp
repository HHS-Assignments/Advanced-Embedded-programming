#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "codeslot.h"
#include "deur.h"
#include "draaideur.h"
#include "hallsensor.h"
#include "schuifdeur.h"
#include "sleutelslot.h"
#include "herkenningsslot.h"
#include "drukbox.h"
#include "kaartslot.h"
#include "idkaart.h"

#include <QPainter>
#include <QLineEdit>
#include <QPen>
#include <QImage>
#include <QPushButton>
#include <QTextBrowser>

namespace {
constexpr int afbeeldingOffset = 10;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sensor(std::make_shared<HallSensor>())
    , voordeurSlot(std::make_shared<SleutelSlot>("geel"))
    , voordeurSlot2(std::make_shared<CodeSlot>(1111))
    , kamerdeur1Slot(std::make_shared<CodeSlot>(1234))
    , kamerdeur1Slot2(std::make_shared<SleutelSlot>("rood"))
    , kamerdeur2Slot(std::make_shared<CodeSlot>(2468))
    , voordeur(nullptr)
    , kamerdeur1(nullptr)
    , kamerdeur2(nullptr)
{
    ui->setupUi(this);
    maakDeuren();

    // Use the widgets that are now part of mainwindow.ui
    idIdInvoer = ui->idIdInvoer;
    idNaamInvoer = ui->idNaamInvoer;
    idAdresInvoer = ui->idAdresInvoer;
    idMaakBtn = ui->idMaakBtn;
    idVerwijderBtn = ui->idVerwijderBtn;
    idGeefToegangBtn = ui->idGeefToegangBtn;
    idHaalToegangBtn = ui->idHaalToegangBtn;
    idOntgrendelBtn = ui->idOntgrendelBtn;

    connect(idMaakBtn, &QPushButton::clicked, this, &MainWindow::on_createIdKaart_clicked);
    connect(idVerwijderBtn, &QPushButton::clicked, this, &MainWindow::on_deleteIdKaart_clicked);
    connect(idGeefToegangBtn, &QPushButton::clicked, this, &MainWindow::on_grantIdKaartToSchuif_clicked);
    connect(idHaalToegangBtn, &QPushButton::clicked, this, &MainWindow::on_revokeIdKaartFromSchuif_clicked);
    connect(idOntgrendelBtn, &QPushButton::clicked, this, &MainWindow::on_ontgrendelSchuifMetId_clicked);

    // Herkennings widgets are created in the .ui file; auto-connected by name
}

void MainWindow::maakDeuren()
{
    deuren.clear();
    deuren.reserve(3);

    // keep a container of all slots in the main window (shared ownership)
    alleSloten.clear();
    alleSloten.push_back(voordeurSlot);
    alleSloten.push_back(voordeurSlot2);
    alleSloten.push_back(kamerdeur1Slot);
    alleSloten.push_back(kamerdeur1Slot2);
    alleSloten.push_back(kamerdeur2Slot);

    voordeur = std::make_shared<Schuifdeur>(489, 162, 80, sensor);
    voordeur->zetSlot(voordeurSlot);
    voordeur->voegSlotToe(voordeurSlot2);
    // add a KaartSlot to the schuifdeur (assignment)
    voordeurKaartSlot = std::make_shared<KaartSlot>("voordeur_kaart");
    alleSloten.push_back(voordeurKaartSlot);
    voordeur->voegSlotToe(voordeurKaartSlot);
    deuren.push_back(voordeur);

    kamerdeur1 = std::make_shared<Draaideur>(285, 286, 30, true);
    kamerdeur1->zetSlot(kamerdeur1Slot);
    kamerdeur1->voegSlotToe(kamerdeur1Slot2);
    // add a KaartSlot to kamerdeur1 as well
    kamerdeur1KaartSlot = std::make_shared<KaartSlot>("kamerdeur1_kaart");
    alleSloten.push_back(kamerdeur1KaartSlot);
    kamerdeur1->voegSlotToe(kamerdeur1KaartSlot);
    deuren.push_back(kamerdeur1);

    kamerdeur2 = std::make_shared<Draaideur>(234, 89, 40, false);
    kamerdeur2->zetSlot(kamerdeur2Slot);
    // create a HerkenningsSlot and add alongside the CodeSlot on deur 3
    herkenningsSlot = std::make_shared<HerkenningsSlot>();
    // default autorisaties for deur 3
    herkenningsSlot->voegAutorisatieToe("Anton", false);
    herkenningsSlot->voegAutorisatieToe("Stefan", true);

    // add to ownership containers and door
    alleSloten.push_back(herkenningsSlot);
    kamerdeur2->voegSlotToe(herkenningsSlot);
    deuren.push_back(kamerdeur2);

    voordeur->openen();
    kamerdeur1->openen();
    kamerdeur2->openen();
}

void MainWindow::paintEvent(QPaintEvent *event){

    QMainWindow::paintEvent(event);

    QPainter painter(this);
    QPen pen;
    QImage image(":/Gebouw.png");

    pen.setColor(Qt::green);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.drawImage(afbeeldingOffset, afbeeldingOffset, image);

    if (sensor) {
        sensor->teken(this);
    }

    for (const auto &deur : deuren) {
        deur->teken(this);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_schuifdeurSensorKnop_clicked()
{
    if (sensor->isGeactiveerd())
        sensor->deactiveer();
    else
        sensor->activeer();

    update();  // belangrijk voor direct hertekenen
}

void MainWindow::on_schuifdeurKnop_clicked()
{
    if (voordeur->isOpen()) {
        voordeur->sluiten();
    } else {
        voordeur->openen();
    }

    update();
}

void MainWindow::on_schuifdeurOntgrendelKnop_clicked()
{
    voordeurSlot->ontgrendel(ui->schuifdeurSleutelInvoer->text().toStdString());
    ui->schuifdeurSleutelInvoer->clear();
    update();
}

void MainWindow::on_schuifdeurOntgrendel2Knop_clicked()
{
    if (voordeurSlot2) {
        voordeurSlot2->ontgrendel(ui->schuifdeurSleutelInvoer2->text().toStdString());
        ui->schuifdeurSleutelInvoer2->clear();
        update();
    }
}

void MainWindow::on_createIdKaart_clicked()
{
    const std::string id = idIdInvoer->text().toStdString();
    const std::string naam = idNaamInvoer->text().toStdString();
    const std::string adres = idAdresInvoer->text().toStdString();
    if (id.empty()) return;

    auto kaart = std::make_shared<IdKaart>(id, naam, adres);
    KaartSlot::voegIdKaartToe(kaart);

    idIdInvoer->clear();
    idNaamInvoer->clear();
    idAdresInvoer->clear();
}

void MainWindow::on_deleteIdKaart_clicked()
{
    const std::string id = idIdInvoer->text().toStdString();
    if (id.empty()) return;
    KaartSlot::verwijderIdKaart(id);
    idIdInvoer->clear();
}

void MainWindow::on_grantIdKaartToSchuif_clicked()
{
    const std::string id = idIdInvoer->text().toStdString();
    if (id.empty() || !voordeurKaartSlot) return;
    auto kaart = KaartSlot::getIdKaart(id);
    if (kaart) {
        kaart->geefToegang(voordeurKaartSlot.get());
    }
    idIdInvoer->clear();
}

void MainWindow::on_revokeIdKaartFromSchuif_clicked()
{
    const std::string id = idIdInvoer->text().toStdString();
    if (id.empty() || !voordeurKaartSlot) return;
    auto kaart = KaartSlot::getIdKaart(id);
    if (kaart) {
        kaart->verwijderToegang(voordeurKaartSlot.get());
    }
    idIdInvoer->clear();
}

void MainWindow::on_ontgrendelSchuifMetId_clicked()
{
    const std::string id = idIdInvoer->text().toStdString();
    if (id.empty() || !voordeurKaartSlot) return;

    if (voordeurKaartSlot->ontgrendel(id)) {
        // if ontgrendelen succeeded, open the door
        voordeur->openen();
    }

    idIdInvoer->clear();
    update();
}

void MainWindow::on_deur2Knop_clicked()
{
    if (kamerdeur1->isOpen()) {
        kamerdeur1->sluiten();
    } else {
        kamerdeur1->openen();
    }

    update();
}

void MainWindow::on_deur2OntgrendelKnop_clicked()
{
    kamerdeur1Slot->ontgrendel(ui->deur2CodeInvoer->text().toStdString());
    ui->deur2CodeInvoer->clear();
    update();
}

void MainWindow::on_deur2Ontgrendel2Knop_clicked()
{
    if (kamerdeur1Slot2) {
        kamerdeur1Slot2->ontgrendel(ui->deur2CodeInvoer2->text().toStdString());
        ui->deur2CodeInvoer2->clear();
        update();
    }
}

void MainWindow::on_deur3Knop_clicked()
{
    if (kamerdeur2->isOpen()) {
        kamerdeur2->sluiten();
        update();
        return;
    }

    const std::string naam = ui->herkenningNaamInvoer->text().toStdString();
    if (naam.empty()) {
        update();
        return;
    }

    if (herkenningsSlot && herkenningsSlot->ontgrendel(naam)) {
        kamerdeur2->openen();
    }

    update();  // belangrijk voor direct hertekenen
}

void MainWindow::on_deur3OntgrendelKnop_clicked()
{
    kamerdeur2Slot->ontgrendel(ui->deur3CodeInvoer->text().toStdString());
    ui->deur3CodeInvoer->clear();
    update();
}

void MainWindow::on_herkenningVoegPos_clicked()
{
    const std::string naam = ui->herkenningNaamInvoer->text().toStdString();
    if (naam.empty()) return;

    // find a Slot pointer and dynamic_cast to HerkenningsSlot as required
    for (const auto &s : alleSloten) {
        if (!s) continue;
        auto h = std::dynamic_pointer_cast<HerkenningsSlot>(s);
        if (h) {
            h->voegAutorisatieToe(naam, true);
            break;
        }
    }

    ui->herkenningNaamInvoer->clear();
}

void MainWindow::on_herkenningVoegNeg_clicked()
{
    const std::string naam = ui->herkenningNaamInvoer->text().toStdString();
    if (naam.empty()) return;

    for (const auto &s : alleSloten) {
        if (!s) continue;
        auto h = std::dynamic_pointer_cast<HerkenningsSlot>(s);
        if (h) {
            h->voegAutorisatieToe(naam, false);
            break;
        }
    }

    ui->herkenningNaamInvoer->clear();
}

void MainWindow::on_herkenningPrint_clicked()
{
    if (!herkenningsSlot) return;
    // associate a Drukbox with the QTextBrowser
    auto druk = std::make_shared<Drukbox>(ui->herkenningBrowser);
    herkenningsSlot->setAfdrukker(druk);
    herkenningsSlot->drukKaartenbak();
}

