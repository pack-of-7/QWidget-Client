#include "mytimer.h"

MyTimer::MyTimer()
{
    //create Timer
    mTimer = new QTimer(this);

    // setup signal and slot
    connect(mTimer,SIGNAL(timeout()),SLOT(myTimerSlots()));
    t_settings = new QSettings();
    qHostname = t_settings->value("mqtt/broker", hostName).toString();
    qPort    = t_settings->value("mqtt/port", port).toInt();
    qAppVersion=t_settings->value("mqtt/applicationsVersion",applications_version).toString();
    qEndpointToken=t_settings->value("mqtt/endpointToken",endpoint_token).toString();

    t_mqttClient = new MqttClient(this);
    t_mqttClient->setPort(qPort);
    t_mqttClient->setHostname(qHostname);
    t_mqttClient->setEndpointToken(qEndpointToken);
    t_mqttClient->setAppVersion(qAppVersion);
    t_settings->sync();

    qDebug() << qPort<<" "<< qHostname<< " " << qEndpointToken << " " << qAppVersion;

    if (t_mqttClient->state() != QMqttClient::Connected)
   {
    t_mqttClient->connectBroker();
        myTimerSlots();
    }else{
         myTimerSlots();
    }
    myTimerSlots();
    //msec
    mTimer->start(6000);
}
void MyTimer::myTimerSlots()
{
             qDebug()<< "timer ...";
             sendData();


}

void MyTimer::sendData()
{
    double temp= (double)QRandomGenerator::global()->bounded(-50, 45);
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

//        QString json1="[{\"temperature\":30,\"humidity\": 63,\"co2\":500,\"battery_level\": 85.7,\"pressure\":400}]";

    QByteArray baMessage=json.toUtf8();
    auto stateString =QString("kp1/%1/dcx/%2/json")
            .arg(qAppVersion)
            .arg(endpoint_token);
    qDebug() << baMessage;
    t_mqttClient->SendStatus(stateString,baMessage);

    //t_mqttClient->disconnectBroker();
}

