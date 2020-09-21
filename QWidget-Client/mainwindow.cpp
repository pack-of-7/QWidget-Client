#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MqttClient.h"
#include "Data.h"
#include "mythreadsobject.h"
#include "threadsObject.h"
#include "mytimer.h"

#include <QtCore/QVariant>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QDateTime>
#include <QtMqtt/QMqttClient>
#include <QtWidgets/QMessageBox>

#include <QMqttStringPair>
#include <QtCore/QJsonObject>
#include <QString>
#include <QSettings>
#include <QRandomGenerator>
#include <QJsonDocument>
#include <QTextStream>
#include <QThread>
#include <QtDebug>
#include <iostream>

using std::cout;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    m_updateSecs(15 * 60),
    m_minUpdateSecs(60)
{
    ui->setupUi(this);


    //connect(mThread,SIGNAL(NumberChanged(int)),this,SLOT(onNumberChanged(int)));
    //connect(mThread,SIGNAL(DoWork(QString, QString)),this,SLOT(onDoWork(QString, QString)));

//    cObject->DoSetup(&cThread);
//    cObject->moveToThread(&cThread);



     m_client = new QMqttClient(this);
     m_client->setHostname(hostName);

     m_settings = new QSettings();
     qHostname = m_settings->value("mqtt/broker", hostName).toString();
     qPort    = m_settings->value("mqtt/port", port).toInt();
     qAppVersion=m_settings->value("mqtt/applicationsVersion",applications_version).toString();
     qEndpointToken=m_settings->value("mqtt/endpointToken",endpoint_token).toString();

     m_mqttClient = new MqttClient(this);
     m_mqttClient->setPort(qPort);
     m_mqttClient->setHostname(qHostname);
     m_mqttClient->setEndpointToken(qEndpointToken);
     m_mqttClient->setAppVersion(qAppVersion);
     m_settings->sync();

     qDebug() << qHostname;
     qDebug() << qPort;
     qDebug()<< "qAppVersion : "<<qAppVersion;
     qDebug() << m_client;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::unsubscribeMqtt(QString state, const QString &hostname, const quint16 port,const QString &id, const QString &appVersion, const QString &endpointTocken)
{
     qDebug() << "unsubscribeMqttConnection";
     //{{HOST_CONNECT}}/kp1/{{APPVERSION_NAME}}/epmx/{{TOKEN}}/get
     //"mqtt.cloud.kaaiot.com/kp1/bt8h4h2ikfmg80udn370-1/epmx/DY5oex7rC3/get"
     qDebug() << hostname << " " << appVersion << " " << endpointTocken;

     auto msg = QString("%1/kp1/%2/epmx/%3/get")
        .arg(hostname)
        .arg(appVersion)
        .arg(endpointTocken);
     //statusBar()->showMessage(msg);
     qDebug() << "msg: " <<  msg;
     qDebug() << "state: " << state;
     m_client->unsubscribe(msg);
}

void MainWindow::subscribeMqtt(QString state, const QString &hostname, const quint16 port,  const QString &id, const QString &appVersion, const QString &endpointTocken)
{
    qDebug() << "subscribeMqttConnection";
    qDebug() << state << " " << hostname << " " << port << " " << appVersion << " " << endpointTocken;

    //{{HOST_CONNECT}}/kp1/{{APPVERSION_NAME}}/epmx/{{TOKEN}}/get
    //"mqtt.cloud.kaaiot.com/kp1/bt8h4h2ikfmg80udn370-1/epmx/DY5oex7rC3/get"
    //auto msg = QString("%1:%2/kp1/%3/epmx/%4/get")
    //  .arg(hostname)
    //  .arg(port)
    auto msg = QString("%1/kp1/%2/epmx/%3/get")
            .arg(hostname)
            .arg(appVersion)
            .arg(endpointTocken);
           // .arg(state);
    //statusBar()->showMessage(msg);
    qDebug() << "subscribeQMttMsg: " <<  msg;
    qDebug() << "state: " << state;

        auto subscription = m_client->subscribe(msg,port);
        qDebug() << __FUNCTION__ << subscription->Subscribed;
        qDebug() << __FUNCTION__ << subscription->SubscriptionPending;

        if (!subscription) {
            //QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
                return;
        }

}


void MainWindow::on_connectButton_clicked()
{
    //connect(m_mqttClient, &MqttClient::HostConnectionUpdate,
      //      this, &MainWindow::updateMqttConnection);
    m_mqttClient->connectBroker();

    qDebug() << "Broker connected: " + hostName;

}

void MainWindow::on_disconnectButton_clicked()
{

    connect(m_mqttClient, &MqttClient::HostConnectionUpdate,
            this, &MainWindow::unsubscribeMqtt);
    m_mqttClient->disconnectBroker();
    qDebug() << "Broker disconnected: "+ hostName;
    //mThread->Stop=true;
    //qDebug() << "stop Stop" << mThread->Stop;

}

void MainWindow::on_publishButton_clicked()
{
   if (m_mqttClient->state() == QMqttClient::Connected)
{

       //'kp1/{APPLICATION_VERSION}/dcx/{ENDPOINT_TOKEN}/json'

        double temp= (double)QRandomGenerator::global()->bounded(15, 45);
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

        QString json1="[{\"temperature\":30,\"humidity\": 63,\"co2\":500,\"battery_level\": 85.7,\"pressure\":400}]";

        QByteArray baMessage=json.toUtf8();
        auto stateString =QString("kp1/%1/dcx/%2/json")
                .arg(qAppVersion)
                .arg(endpoint_token);
        m_mqttClient->SendStatus(stateString,baMessage);
    }
   else
   {
       QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish. Is there a valid connection?"));
        return;
   }
}



void MainWindow::onDoWork(QString &qAppVersion, QString &endpoint_token)
{
    qDebug() << "mThread without number ";
    for(int i =0; i<20; i++)
    {
        qDebug() << i;

        double temp= (double)QRandomGenerator::global()->bounded(15, 45);
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
                .arg(endpoint_token);
        m_mqttClient->SendStatus(stateString,baMessage);
    }

}
