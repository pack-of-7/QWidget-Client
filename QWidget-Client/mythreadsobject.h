#ifndef MYTHREADOBJECT_H
#define MYTHREADOBJECT_H

#include "mainwindow.h"
#include <QThread>
#include <QSettings>
#include <QtCore>
#include <QString>
#include <QObject>

class MyThreadsObject : public QThread
{
    Q_OBJECT
public:

   explicit MyThreadsObject(QObject *parent=0);
    void run();
    bool Stop;


signals:
    void NumberChanged(int);
    void DoWork(QString &qAppVersion, QString &endpoint_token);

public slots:

private:
 QSettings   *td_settings;        //< access to our settings
 MqttClient  *td_mqttClient;
//  QString hostName="mqtt.cloud.kaaiot.com";
//  QString endpoint_token = "DY5oex7rC3";       // Paste your endpoint token
//  QString applications_version = "bt8h4h2ikfmg80udn370-1";
//  int port = 1883;
 QString qHostname ="";
 quint16 qPort;
 QString qAppVersion="";
 QString qEndpointToken="";

};

#endif // MYTHREADOBJECT_H
