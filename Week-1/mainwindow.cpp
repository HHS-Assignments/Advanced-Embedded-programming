#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include "hallsensor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s1=new HallSensor();
}


void MainWindow::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    QPen pen;
    QImage image("/home/tom/Git/Advanced-Embedded-programming/Week-1/Gebouw.png");

    pen.setColor(Qt::green);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.drawImage(10,10,image);

    s1->teken(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_schuifdeurSensorKnop_clicked()
{
    if (s1->isGeactiveerd())
        s1->deactiveer();
    else
        s1->activeer();

    update();  // belangrijk voor direct hertekenen

}

