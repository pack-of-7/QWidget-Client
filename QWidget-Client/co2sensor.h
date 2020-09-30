#ifndef CO2SENSOR_H
#define CO2SENSOR_H

#include <QMainWindow>
#include <QObject>
#include <QTimer>
#include <MqttClient.h>
#include <QSettings>
#include <QDebug>
#include <QRandomGenerator>

#include "co2sensorif.h"

class CO2Sensor: public CO2SensorIF
{
public:
    CO2Sensor(QObject *parent = nullptr);
    void myTimerSlots();
    void sendDataCo2();
    void sendDataSweepGas();

private:
    QTimer  *m_sendCO2Timer;
    float   m_lastCO2;
    float   m_lastSweepGas;

    QSettings   *t_settings;        //< access to our settings
    MqttClient  *t_mqttClient;

    QString hostName="mqtt.cloud.kaaiot.com";    // Paste your host token
    QString endpoint_token = "DY5oex7rC3";       // Paste your endpoint token
    QString applications_version = "bt8h4h2ikfmg80udn370-1"; // Paste your appVersion token
    int port = 1883;
    QString qHostname ="";
    quint16 qPort;
    QString qAppVersion="";
    QString qEndpointToken="";
};

#endif // CO2SENSOR_H
