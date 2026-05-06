#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class QPaintEvent;
class Deur;
class Draaideur;
class HallSensor;
class Schuifdeur;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_schuifdeurSensorKnop_clicked();
    void on_schuifdeurKnop_clicked();
    void on_draaideur1Knop_clicked();
    void on_draaideur2Knop_clicked();

private:
    void maakDeuren();

    Ui::MainWindow *ui;
    std::shared_ptr<HallSensor> sensor;
    std::vector<std::shared_ptr<Deur>> deuren;
    std::shared_ptr<Schuifdeur> voordeur;
    std::shared_ptr<Draaideur> kamerdeur1;
    std::shared_ptr<Draaideur> kamerdeur2;
};

#endif // MAINWINDOW_H
