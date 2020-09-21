#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMqttClient>
#include <QString>
#include <string>
#include <QtCore/QVariant>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QTimer>

#include "MqttClient.h"
#include "data.h"
#include "mythreadsobject.h"
#include "threadsObject.h"
#include "mytimer.h"

using std::string;

class QVariant;
class QByteArray;
class QStringList;
class QSettings;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



    QString hostName="mqtt.cloud.kaaiot.com";
    QString endpoint_token = "DY5oex7rC3";       // Paste your endpoint token
    QString applications_version = "bt8h4h2ikfmg80udn370-1";
    int port = 1883;
    QString qHostname ="";
    quint16 qPort;
    QString qAppVersion="";
    QString qEndpointToken="";

    public slots:

    void    subscribeMqtt(QString state, const QString &hostname,
                                 const quint16 port,  const QString &id, const QString &appVersion, const QString &endpointToken);
    void    unsubscribeMqtt(QString state, const QString &hostname,
                                 const quint16 port,  const QString &id, const QString &appVersion, const QString &endpointToken);
    void    onDoWork(QString &qAppVersion, QString &endpoint_token);


private slots:

    void on_connectButton_clicked();

    void on_disconnectButton_clicked();

    void on_publishButton_clicked();

    void on_subscibeButton_clicked();

    void on_startButton_clicked();

    void on_stopButton_clicked();

    void on_serverInfoButton_clicked();

private:
    Ui::MainWindow *ui;
     QMqttClient    *m_client;
     MqttClient     *m_mqttClient;      //< the MQTT Client
     QSettings      *m_settings;        //< access to our settings
     int            m_updateSecs;       //< the number of minutes between updates
     int            m_minUpdateSecs;    //< minimum time between updates (for API)
     QTimer         *m_updateTimer;
     MyTimer        *m_myTimer;
     Data *m_data;
    // QThread *m_td;
//     QThread *cThread;
//     ThreadsObject cObject;
     //QThread *mThread;
    //ThreadsObject *mThread;


};
#endif // MAINWINDOW_H
