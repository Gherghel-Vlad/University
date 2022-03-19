#include "EthnographicPark.h"
#include "EthnologistGUI.h"
#include "Observer.h"
EthnographicPark::EthnographicPark(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void EthnographicPark::start_program(EthnologistsService* _ethServ, BuildingsService* _buildServ){

    this->ethServ = _ethServ;
    this->buildServ = _buildServ;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < this->ethServ->getEthnologistVector().size(); i++) {
        this->qcolorVector.push_back(QColor(rand() % 256, rand() % 256, rand() % 256));
    }

    for (int i = 0; i < this->ethServ->getEthnologistVector().size(); i++) {
        EthnologistGUI* egui = new EthnologistGUI();
        this->ethWindowsVector.push_back(egui);
        this->ethWindowsVector[i]->start_window(this->ethServ, this->buildServ, this->ethServ->getEthnologistVector()[i], this->qcolorVector[i]);
        /*this->buildServ->addObserver(egui);
        this->ethServ->addObserver(egui);*/
    }

}
