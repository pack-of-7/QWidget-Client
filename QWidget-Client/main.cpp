#include "mainwindow.h"

#include <QApplication>
#include "co2sensor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CO2Sensor  co2Temp;
    MainWindow w(&co2Temp);
    //MainWindow w;
    w.show();
    return a.exec();
}
