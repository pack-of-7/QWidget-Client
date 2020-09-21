#ifndef THREADSDONERIGHT_H
#define THREADSDONERIGHT_H

#include "MqttClient.h"
#include "mythread.h"
#include <QThread>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>
#include <QMessageBox>
#include <QtCore>

#include <mainwindow.h>

class ThreadsObject : public QThread
//class ThreadsObject : public QObject
{
    Q_OBJECT
public:
   explicit ThreadsObject(QObject *parent=0);
    void DoSetup(QThread &cThread);


public slots:
    //void DoWork(QString , QString );
    void DoWork();
    void sendData();

private:
     MqttClient  *td_mqttClient;
     QString qHostname ="";
     quint16 qPort;
     QString qAppVersion="";
     QString qEndpointToken="";
     QSettings *td_settings;
     MyThread *mThread;

};

#endif // THREADSDONERIGHT_H
