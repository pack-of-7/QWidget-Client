#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMqttClient>
#include <QString>
#include <QtCore/QVariant>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QTimer>
#include <QStandardItem>
#include <QList>
#include <QVariant>
#include <QtQml/QJSEngine>
#include <QtQml/QQmlContext>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QPointF>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartGlobal>

#include "mqttclient.h"
#include "co2sensor.h"

using std::string;

class QVariant;
class QByteArray;
class QStringList;
class QSettings;

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Q_PROPERTY(QPointF lastReadingSweepGas READ lastReadingSweepGas WRITE setLastReadingSweepGas NOTIFY newReadingSweepGas)
    Q_PROPERTY(QPointF lastReadingCO2 READ lastReadingCO2 WRITE setLastReadingCO2 NOTIFY newReadingCO2)

public:
    MainWindow(CO2SensorIF *co2Sensor, QWidget *parent = nullptr);
    ~MainWindow();

    QPointF lastReadingSweepGas() const;
    QPointF lastReadingCO2() const;
    void setLastReadingSweepGas(const QPointF &lastReading);
    void setLastReadingCO2(const QPointF &lastReading);


    QString hostName="mqtt.cloud.kaaiot.com";
    QString endpoint_token = "DY5oex7rC3";
    QString applications_version = "bt8h4h2ikfmg80udn370-1";
    int port = 1883;
    QString qHostname ="";
    quint16 qPort;
    QString qAppVersion="";
    QString qEndpointToken="";

    public slots:

signals:
    void newReadingCO2();
    void newReadingSweepGas();

private slots:

    void co2Update(QDateTime timestamp, float co2);
    void sweepGasFlowUpdate(QDateTime timestamp, float sweepGas);

//    void dataUpdate();


private:
    Ui::MainWindow  *ui;
    QPointF         m_lastReadingCO2;
    QPointF         m_lastReadingSweepGas;

    QMqttClient     *m_client;
    MqttClient      *m_mqttClient;      //< the MQTT Client
    QSettings       *m_settings;        //< access to our settings

    CO2SensorIF     *m_co2Sensor;  //< the temperature sensor we use

};
#endif // MAINWINDOW_H
