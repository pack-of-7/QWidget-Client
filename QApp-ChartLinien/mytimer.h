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
#include <QtWidgets/QTextEdit>
#include <QCategoryAxis>
#include <QColor>
#include <QColorDialog>
#include <QPalette>
#include <QtWidgets/QStyle>
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
    QTimer          *mTimer;


public slots:
    void myTimerSlots();
    void sendData();

private:
    QSettings       *t_settings;        //< access to our settings
    MqttClient      *t_mqttClient;

    QString         hostName="mqtt.cloud.kaaiot.com";    // Paste your host token
    QString         endpoint_token = "DY5oex7rC3";       // Paste your endpoint token
    QString         applications_version = "bt8h4h2ikfmg80udn370-1"; // Paste your appVersion token
    int             port = 1883;
    QString         qHostname ="";
    quint16         qPort;
    QString         qAppVersion="";
    QString         qEndpointToken="";

    QWidget         *dataWidget;
    QWidget         *chartWidget;

    QGraphicsScene  *scene;

    QMainWindow     m_wChart;
    QMainWindow     m_wData;

    QGridLayout     *mainLayout;
    QVBoxLayout     *co2Layout;
    QVBoxLayout     *sweepGasLayout;
    QHBoxLayout     *chartLayout;
    QHBoxLayout     *dataLayout;
    QHBoxLayout     *statusLayout;

    QChart          *chart;
    QChartView      *chartView;
    QLineSeries     *seriesCo2;
    QLineSeries     *seriesSweepGas;

    QDateTimeAxis   *axisX;
    QValueAxis      *axisY;
    QValueAxis      *axisY_1;
    QValueAxis      *axisY_2;

//    QCategoryAxis *axisCX;
//    QCategoryAxis *axisCY;
//    QCategoryAxis *axisCY_1;
//    QCategoryAxis *axisCY_2;

    QLabel          *lblCo2;
    QLabel          *lblCo2Data;
    QLabel          *lblSweepGas;
    QLabel          *lblSweepGasData;
    QLabel          *lblStatus;
    QLabel          *lblOnOff;

    QPalette        *pallete;
    QColor          *color;
    QStyle          *style;

};

#endif // MYTIMER_H
