#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SimulationExam.h"
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QPainterPath>
#include <QLabel>
#include <QHBoxLayout>

class SimulationExam : public QMainWindow
{
    Q_OBJECT

public:
    SimulationExam(QWidget *parent = Q_NULLPTR);

    void start_program();

private:


    Ui::SimulationExamClass ui;

    QHBoxLayout* h;
    QWidget* w;
    QVBoxLayout* v;
    QLabel* lbl;
    void paintEvent(QPaintEvent* event) override;
};
