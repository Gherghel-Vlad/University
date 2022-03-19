#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtWidgetsApplication1Class ui;

    QHBoxLayout* hbl = nullptr;

    QLabel* lbl = nullptr;

    QWidget* w;
};
