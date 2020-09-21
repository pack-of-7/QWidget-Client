#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QtCore>
#include <QDebug>

class MyThread:public QThread
{
public:
    MyThread();
    void run();
    QString name;
    bool Stop;
};

#endif // MYTHREAD_H
