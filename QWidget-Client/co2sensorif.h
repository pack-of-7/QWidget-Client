#ifndef CO2SENSOREIF_H
#define CO2SENSOREIF_H

#include <QMainWindow>
#include <QObject>
#include <QTimer>
#include <mqttclient.h>
#include <QSettings>
#include <QDebug>
#include <QRandomGenerator>
class CO2SensorIF : public QObject
{
    Q_OBJECT
private:
     QTimer  *m_sendCO2TimerIf;
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
public:
   explicit CO2SensorIF(QObject *parent = nullptr);
signals:
    void newCO2(QDateTime timestamp, float co2);
    void newSweepGas(QDateTime timestamp, float sweepGas);
    void newCo2Gas(QDateTime timestamp,float co2, float sweepGas);

public slots:
    void myTimerSlots();
     void sendDataCo2();
     void sendDataSweepGas();
     void sendDataCo2Gas();
     QString getData();


};

#endif // CO2SENSOREIF_H
