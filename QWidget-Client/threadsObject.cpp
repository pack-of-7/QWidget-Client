#include "threadsObject.h"
#include <QMessageBox>
#include <QtCore>

ThreadsObject::ThreadsObject(QObject *parent):
    QThread(parent)
{

     // td_mqttClient->connectBroker();


}

void ThreadsObject::DoSetup(QThread &cThread)
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

    td_mqttClient->connectBroker();


    if (td_mqttClient->state() == QMqttClient::Connected){
        for(int i =0; i<10; i++)
        {
    //        mThread = new MyThread(this);

        //connect(&cThread,SIGNAL(started()),this,SLOT(DoWork(QString qAppVersion, QString endpoint_token)));
         connect(&cThread, &QThread::started,this, &ThreadsObject::DoWork);
         i++;
    //     mThread->start();
    //     mThread->Stop=false;
    //     mThread->msleep(1000);
    //     mThread->Stop=true;

        }
    }
    else
    {
        qDebug() << "Is not connected!";


         //td_mqttClient->connectBroker();
    }
     //td_mqttClient->disconnect();
}

void ThreadsObject::DoWork()
{

    if (td_mqttClient->state() != QMqttClient::Connected)
   {
        td_mqttClient->connectBroker();
         qDebug() << "";
         sendData();
    }
    else
    {
        sendData();
    }

}
void ThreadsObject::sendData()
{
    double temp= (double)QRandomGenerator::global()->bounded(-55, 45);
    double humidity= (double)QRandomGenerator::global()->bounded(0, 100);
    int co2 = QRandomGenerator::global()->bounded(100, 2000);
    double battery_level= (double)QRandomGenerator::global()->bounded(0, 1000);
    int pressure= QRandomGenerator::global()->bounded(100, 2000);
    qDebug() << temp << " " << humidity << " " << co2 << " " << battery_level<< " " << pressure;
    QString json = QString("[{\"temperature\":%1,\"humidity\": %2,\"co2\":%3,\"battery_level\": %4,\"pressure\":%5}]")
           .arg(temp)
           .arg(humidity)
           .arg(co2)
           .arg(battery_level)
           .arg(pressure);

    QByteArray baMessage=json.toUtf8();
    auto stateString =QString("kp1/%1/dcx/%2/json")
            .arg(qAppVersion)
            .arg(qEndpointToken);

    td_mqttClient->SendStatus(stateString,baMessage);
}
