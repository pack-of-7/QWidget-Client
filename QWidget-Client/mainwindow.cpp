#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mqttclient.h"
#include "co2sensorif.h"
#include <QtCore/QVariant>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QDateTime>
#include <QMqttClient>
#include <QtMqtt/QMqttClient>
#include <QtWidgets/QMessageBox>
#include <QMqttStringPair>
#include <Qt>
#include <QString>
#include <QSettings>
#include <QRandomGenerator>
#include <QJsonDocument>
#include <QtDebug>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>

#include <iostream>
using std::cout;

MainWindow::MainWindow(CO2SensorIF *co2Sensor, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_co2Sensor(co2Sensor)

{
    ui->setupUi(this);
    this->setWindowTitle("Dashboard");
    connect(m_co2Sensor, &CO2SensorIF::newCO2, this, &MainWindow::co2Update);
    connect(m_co2Sensor, &CO2SensorIF::newSweepGas, this, &MainWindow::sweepGasFlowUpdate);
    connect(co2Sensor->t_mqttClient, &MqttClient::HostConnectionUpdate,
            this, &MainWindow::updateMqttConnection);

    ui->quickWidget->engine()->rootContext()->setContextProperty("CO2Data", this);
    ui->quickWidget->engine()->rootContext()->setContextProperty("SweepGasData", this);
    ui->quickWidget->setSource(QUrl("qrc:/Chart.qml"));
    ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

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
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::updateMqttConnection(QString msgStatus, QString state, const QString &hostname, const quint16 port, const QString &id)
{
    auto statusMsg=QString("Status: %1").arg(msgStatus);

    qDebug() << "msgStatus: "<< msgStatus;
   // QString htmlMsg=Qt
    QString msg = statusMsg;
    qDebug() << "msg: "<< msg;
//    if(msg == "Status: OFF")
//    {
//        QMessageBox msgBox;
//        msgBox.information(this, "MQTT Connection Information", statusMsg);

//    }

//   show a message box with the information
//   QMessageBox::information(this, "MQTT Connection Information", statusMsg);

//     Update the bottom statusBar with the status information.
    statusBar()->showMessage(msg);
}

void MainWindow::setStatusConnected(const QString &status){
    m_status=status;
}
void MainWindow::setStatusDisconnected(const QString &status){
    m_status=status;
}

QString MainWindow::statusConnected() const{
    return m_status;
}

QString MainWindow::statusDisconnected() const{
    return m_status;
}


void MainWindow::co2Update(QDateTime timestamp, float co2)
{
    // ** update the m_lastReading **
    double xVal = timestamp.toMSecsSinceEpoch();
    qDebug() << "xVal" << xVal << ", co2" << co2;
    setLastReadingCO2(QPointF(xVal, co2));
}

void MainWindow::sweepGasFlowUpdate(QDateTime timestamp, float sweepGas)
{
    // ** update the m_lastReading **
    double xVal = timestamp.toMSecsSinceEpoch();

    qDebug() << "xVal" << xVal << ", sweepGas" << sweepGas;
    setLastReadingSweepGas(QPointF(xVal, sweepGas));
}

void MainWindow::setLastReadingCO2(const QPointF &lastReading)
{
    //qDebug() << "setLastReadingCO2: " << lastReading;
    m_lastReadingCO2 = lastReading; 

    emit newReadingCO2();
}

QPointF MainWindow::lastReadingCO2() const
{
    //qDebug() << "return lastReadingCO2: " << m_lastReadingCO2;
    return m_lastReadingCO2;
}
void MainWindow::setLastReadingSweepGas(const QPointF &lastReading)
{
    //qDebug() << "setLastReadingSweepGas: " << lastReading;
    m_lastReadingSweepGas = lastReading;    

    emit newReadingSweepGas();
}

QPointF MainWindow::lastReadingSweepGas() const
{
    //qDebug() << "lastReadingSweepGas: " << m_lastReadingSweepGas;
    return m_lastReadingSweepGas;
}
