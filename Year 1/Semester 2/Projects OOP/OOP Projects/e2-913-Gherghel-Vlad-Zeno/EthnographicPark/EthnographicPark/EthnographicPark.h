#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EthnographicPark.h"
#include "BuildingsService.h"
#include "EthnologistsService.h"
#include "EthnologistGUI.h"

class EthnographicPark : public QMainWindow
{
    Q_OBJECT

public:
    EthnographicPark(QWidget *parent = Q_NULLPTR);

    void start_program(EthnologistsService* _ethServ, BuildingsService* _buildServ);
private:
    EthnologistsService* ethServ;
    BuildingsService* buildServ;
    vector<QColor> qcolorVector;
    vector<EthnologistGUI*> ethWindowsVector;

    Ui::EthnographicParkClass ui;
};
