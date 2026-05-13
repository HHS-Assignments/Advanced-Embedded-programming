#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "codeslot.h"
#include "deur.h"
#include "draaideur.h"
#include "hallsensor.h"
#include "schuifdeur.h"
#include "sleutelslot.h"

#include <QPainter>
#include <QLineEdit>
#include <QPen>
#include <QImage>

namespace {
constexpr int afbeeldingOffset = 10;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , sensor(std::make_shared<HallSensor>())
    , voordeurSlot(std::make_shared<SleutelSlot>("geel"))
    , kamerdeur1Slot(std::make_shared<CodeSlot>(1234))
    , kamerdeur2Slot(std::make_shared<CodeSlot>(2468))
    , voordeur(nullptr)
    , kamerdeur1(nullptr)
    , kamerdeur2(nullptr)
{
    ui->setupUi(this);
    maakDeuren();
}

void MainWindow::maakDeuren()
{
    deuren.clear();
    deuren.reserve(3);

    voordeur = std::make_shared<Schuifdeur>(489, 162, 80, sensor);
    voordeur->zetSlot(voordeurSlot.get());
    deuren.push_back(voordeur);

    kamerdeur1 = std::make_shared<Draaideur>(285, 286, 30, true);
    kamerdeur1->zetSlot(kamerdeur1Slot.get());
    deuren.push_back(kamerdeur1);

    kamerdeur2 = std::make_shared<Draaideur>(234, 89, 40, false);
    kamerdeur2->zetSlot(kamerdeur2Slot.get());
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

void MainWindow::on_draaideur1Knop_clicked()
{
    if (kamerdeur1->isOpen()) {
        kamerdeur1->sluiten();
    } else {
        kamerdeur1->openen();
    }

    update();
}

void MainWindow::on_draaideur1OntgrendelKnop_clicked()
{
    kamerdeur1Slot->ontgrendel(ui->draaideur1CodeInvoer->text().toStdString());
    ui->draaideur1CodeInvoer->clear();
    update();
}

void MainWindow::on_draaideur2Knop_clicked()
{
    if (kamerdeur2->isOpen()) {
        kamerdeur2->sluiten();
    } else {
        kamerdeur2->openen();
    }

    update();  // belangrijk voor direct hertekenen
}

void MainWindow::on_draaideur2OntgrendelKnop_clicked()
{
    kamerdeur2Slot->ontgrendel(ui->draaideur2CodeInvoer->text().toStdString());
    ui->draaideur2CodeInvoer->clear();
    update();
}

