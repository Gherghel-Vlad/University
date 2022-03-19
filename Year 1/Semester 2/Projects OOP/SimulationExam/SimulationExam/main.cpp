#include "SimulationExam.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimulationExam w;
    w.show();
    return a.exec();
}
