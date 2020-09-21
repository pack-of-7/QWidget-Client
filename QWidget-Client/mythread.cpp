#include "mythread.h"
#include <QtCore>
#include <QDebug>

MyThread::MyThread()
{

}

void MyThread::run(){

    // run
    //qDebug()<<this->name << "is running";
    qDebug() << this->objectName() << "Thread is running";
    Stop = false;
    for(int i=0; i<10;i++){
        QMutex mutex;
        mutex.lock();
        if(this->Stop){
            break;
        }
        mutex.unlock();

        this->msleep(2000);

        //qDebug() << this->name << i;
        qDebug() << this->objectName() << i;
    }
}
