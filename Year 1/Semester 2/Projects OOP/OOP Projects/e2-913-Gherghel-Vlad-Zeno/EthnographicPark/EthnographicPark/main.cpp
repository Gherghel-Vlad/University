#include "EthnographicPark.h"
#include <QtWidgets/QApplication>
#include "BuildingsService.h"
#include "EthnologistsService.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EthnographicPark w;

    BuildingsRepository* bRepo = new BuildingsRepository();
    EthnologistsRepository* eRepo = new EthnologistsRepository();

    BuildingsService* bService = new BuildingsService(bRepo);
    EthnologistsService* eService = new EthnologistsService(eRepo);


    w.start_program(eService, bService);
    return a.exec();
}
