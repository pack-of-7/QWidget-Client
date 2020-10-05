#include "co2sensorif.h"
#include <QDebug>
#include <QTimer>

CO2SensorIF::CO2SensorIF(QObject *parent) : QObject(parent)
{

    m_sendCO2TimerIf = new QTimer(this);
    connect(m_sendCO2TimerIf,SIGNAL(timeout()),this,SLOT(myTimerSlots()));

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
        qDebug()<< "if";
        myTimerSlots();
    }else{
        qDebug()<< "else";
         myTimerSlots();
    }

    m_sendCO2TimerIf->setInterval(4000);
    m_sendCO2TimerIf->setSingleShot(false);
    m_sendCO2TimerIf->start();
}
void CO2SensorIF::myTimerSlots()
{
    qDebug()<< "timer ...";

    //Data send
    sendDataSweepGas();
    sendDataCo2();
}

void CO2SensorIF::sendDataCo2()
{
    float co2 =(float)QRandomGenerator::global()->bounded(100, 1000);
    QString json = QString("[{\"co2\":%1}]").arg(co2);

    QByteArray baMessage=json.toUtf8();
    auto stateString =QString("kp1/%1/dcx/%2/json")
            .arg(qAppVersion)
            .arg(endpoint_token);
    t_mqttClient->SendStatus(stateString,baMessage);

    QDateTime now = QDateTime::currentDateTime();
    qDebug()<< "date: " << now;
    m_lastCO2 = co2;
    qDebug() << "m_lastCO2 : " <<m_lastCO2 ;

    emit newCO2(now, m_lastCO2);
}
void CO2SensorIF::sendDataSweepGas()
{
    qDebug() << "sendDataSweepGas";
    float pressure= (float)QRandomGenerator::global()->bounded(100, 2000);
    QString json = QString("[{\"pressure\":%1}]").arg(pressure);

    QByteArray baMessage=json.toUtf8();
    auto stateString =QString("kp1/%1/dcx/%2/json")
            .arg(qAppVersion)
            .arg(endpoint_token);
    t_mqttClient->SendStatus(stateString,baMessage);
    QDateTime now = QDateTime::currentDateTime();
    qDebug()<< "date: " << now;
    m_lastSweepGas = pressure;
    qDebug() << " m_lastSweepGas : " << m_lastSweepGas ;

    emit newSweepGas(now, m_lastSweepGas);
}

QString CO2SensorIF::getData()
{
    double temp= (double)QRandomGenerator::global()->bounded(-50, 45);
    double humidity= (double)QRandomGenerator::global()->bounded(0, 100);
    float co2 =(float)QRandomGenerator::global()->bounded(100, 1000);
    double battery_level= (double)QRandomGenerator::global()->bounded(0, 1000);
    float pressure= (float)QRandomGenerator::global()->bounded(100, 2000);
    qDebug() << temp << " " << humidity << " " << co2 << " " << battery_level<< " " << pressure;
    QString jsonString = QString("[{\"temperature\":%1,\"humidity\": %2,\"co2\":%3,\"battery_level\": %4,\"pressure\":%5}]")
           .arg(temp)
           .arg(humidity)
           .arg(co2)
           .arg(battery_level)
           .arg(pressure);
    return jsonString;
}
void CO2SensorIF::sendDataCo2Gas()
{

}
