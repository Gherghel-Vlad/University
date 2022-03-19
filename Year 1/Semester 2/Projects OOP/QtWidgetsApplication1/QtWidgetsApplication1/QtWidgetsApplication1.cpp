#include "QtWidgetsApplication1.h"

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    this->w = new QWidget();
    auto* mainLayout = new QVBoxLayout();
    auto* btn = new QPushButton("asd");
    mainLayout->addWidget(btn);
    this->lbl = new QLabel(this);
    this->lbl->setText("ghdaffdafsda");
    this->hbl = new QHBoxLayout();
    this->hbl->addWidget(this->lbl);

    this->layout()->addWidget(this->lbl);
    this->w->setLayout(this->hbl);
    
    this->w->show();
}
