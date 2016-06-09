#include <QApplication>
#include "formclock.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    FormClock clock;
   //clock.resize(200, 100);
    clock.show();

    return app.exec();
}
