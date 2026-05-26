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
class Slot;
class CodeSlot;
class Schuifdeur;
class SleutelSlot;

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
    void on_schuifdeurOntgrendelKnop_clicked();
    void on_schuifdeurOntgrendel2Knop_clicked();
    void on_draaideur1Knop_clicked();
    void on_draaideur1OntgrendelKnop_clicked();
    void on_draaideur1Ontgrendel2Knop_clicked();
    void on_draaideur2Knop_clicked();
    void on_draaideur2OntgrendelKnop_clicked();
    void on_herkenningVoegPos_clicked();
    void on_herkenningVoegNeg_clicked();
    void on_herkenningPrint_clicked();

private:
    void maakDeuren();

    Ui::MainWindow *ui;
    std::shared_ptr<HallSensor> sensor;
    std::shared_ptr<SleutelSlot> voordeurSlot;
    std::shared_ptr<CodeSlot> voordeurSlot2;
    std::shared_ptr<CodeSlot> kamerdeur1Slot;
    std::shared_ptr<SleutelSlot> kamerdeur1Slot2;
    std::shared_ptr<CodeSlot> kamerdeur2Slot;
    std::vector<std::shared_ptr<Slot>> alleSloten;
    std::vector<std::shared_ptr<Deur>> deuren;
    std::shared_ptr<Schuifdeur> voordeur;
    std::shared_ptr<Draaideur> kamerdeur1;
    std::shared_ptr<Draaideur> kamerdeur2;
    std::shared_ptr<class HerkenningsSlot> herkenningsSlot;

};

#endif // MAINWINDOW_H
