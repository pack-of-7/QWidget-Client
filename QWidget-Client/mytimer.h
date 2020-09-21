#ifndef MYTIMER_H
#define MYTIMER_H

#include <QMainWindow>
#include <QObject>
#include <QTimer>
#include <MqttClient.h>
#include <QSettings>

class MyTimer:public QObject
{
    Q_OBJECT
public:
    MyTimer();
    QTimer *mTimer;


public slots:
    void myTimerSlots();
    void sendData();

private:
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

#endif // MYTIMER_H
