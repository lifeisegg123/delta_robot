#include "DeltaUi.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    delta::DeltaUi* test = new delta::DeltaUi;
    test->show();

    return app.exec();
}