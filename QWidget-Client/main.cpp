#include "mainwindow.h"
#include "mythread.h"
#include "threadsObject.h"
#include "mytimer.h"
#include "myserver.h"
#include "mymultiserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

// ***********************
//    ** Mit QTimer funktioniert


    MyTimer mtimer;
    mtimer.myTimerSlots();

// ************************
// ** funktioniert noch nicht

//    QThread cThread;
//    ThreadsObject cObject;
//    cObject.DoSetup(cThread);
//    cObject.moveToThread(&cThread);

//    cThread.start();

//    //    cThread.msleep(2000);

    return a.exec();
}

//************************
//    MyMultiServer myServer;
//    myServer.startServer();
//************************
//    MyServer mServer;
//***********************
