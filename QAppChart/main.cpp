#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QCoreApplication>
#include <QApplication>

#include "mytimer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyTimer mtimer;
    return a.exec();
}
