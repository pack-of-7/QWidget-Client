#ifndef MYTIMER_H
#define MYTIMER_H

#include <QMainWindow>
#include <QObject>
#include <QTimer>
#include <QSettings>
#include <QDebug>
#include <QRandomGenerator>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QColor>
#include <QPalette>
#include "mqttclient.h"


QT_BEGIN_NAMESPACE
class QGraphicsScene;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE


class MyTimer : public QObject
{
    Q_OBJECT
public:
    explicit MyTimer(QObject *parent = nullptr);
    //MyTimer();
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

    QWidget *dataWidget;
    QWidget *chartWidget;

    QGraphicsScene *scene;

    QMainWindow     m_wChart;
    QMainWindow     m_wData;

    QGridLayout *mainLayout;
    QVBoxLayout *co2Layout;
    QVBoxLayout *sweepGasLayout;
    QHBoxLayout *chartLayout;
    QHBoxLayout *dataLayout;

    QChart          *chart;
    QChartView      *chartView;
    QSpacerItem     *spItCo2;
    QSpacerItem     *spItGas;

    QSplineSeries   *splSeriesCO2;
    QSplineSeries   *splSeriesSweepGas;
    QDateTimeAxis   *axisX;
    QValueAxis      *axisY;
    QValueAxis      *axisY_1;
    QValueAxis      *axisY_2;

    QLabel *lblCo2 = new QLabel("CO2 Removal");
    QLabel *lblCo2Data;
    QLabel *lblSweepGas = new QLabel("Sweep Gas Flow");
    QLabel *lblSweepGasData;

};

#endif // MYTIMER_H
