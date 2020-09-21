#include "mythreadsobject.h"
#include "mainwindow.h"
#include <QtCore>
#include <QSettings>
#include <QString>

MyThreadsObject::MyThreadsObject(QObject *parent):
    QThread(parent)
{
    QString hostName="mqtt.cloud.kaaiot.com";
    QString endpoint_token = "DY5oex7rC3";       // Paste your endpoint token
    QString applications_version = "bt8h4h2ikfmg80udn370-1";
    int port = 1883;
    td_settings = new QSettings();
    qHostname = td_settings->value("mqtt/broker", hostName).toString();
    qPort    = td_settings->value("mqtt/port", port).toInt();
    qAppVersion=td_settings->value("mqtt/applicationsVersion",applications_version).toString();
    qEndpointToken=td_settings->value("mqtt/endpointToken",endpoint_token).toString();

    td_mqttClient = new MqttClient(this);
    td_mqttClient->setPort(qPort);
    td_mqttClient->setHostname(qHostname);
    td_mqttClient->setEndpointToken(qEndpointToken);
    td_mqttClient->setAppVersion(qAppVersion);
    td_settings->sync();

//    mTrObj = new MyThreadsObject(this);
//    connect()
}

void MyThreadsObject::run()
{

    // run


     Stop = false;
    for(int i=0; i<10;i++)
    {

        QMutex mutex;
        mutex.lock();
        qDebug() << "Stop " << Stop ;
        if(this->Stop) break;
        mutex.unlock();

        emit NumberChanged(i);

        //emit DoWork(qAppVersion,endpoint_token);

        this->msleep(1000);
        qDebug() << "Stop Ende" << Stop ;

    }
     Stop=true;
}
