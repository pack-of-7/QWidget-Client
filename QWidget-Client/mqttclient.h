#ifndef MQQTCLIENT_H
#define MQQTCLIENT_H

#include <QMqttClient>
#include <QObject>
#include <QtCore/QByteArray>
#include <QMqttSubscription>
#include <QMessageBox>
#include <QMetaType>
#include <QCoreApplication>
#include <QRandomGenerator>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QJsonObject>
#include <QtCore/QJsonObject>
#include <QMqttSubscription>
#include <QTime>
#include <QDateTime>

class MqttClient : public QObject
{
    Q_OBJECT

public:
    MqttClient(QObject *parent = nullptr);
    MqttClient();
    virtual ~MqttClient();

    void connectBroker();
    void disconnectBroker();

    QString hostname() const;
    void setHostname(const QString &hostname);

    quint16 port() const;
    void setPort(quint16 port);

    QString deviceName() const;
    void setDeviceName(const QString &deviceName);

    QString endpointToken() const;
    void setEndpointToken(const QString &endpointToken);

    QString appVersion() const;
    void setAppVersion(const QString &appVersion);

    QString turnData() const;
    void setTurnData(const QString &turnOnOff);
    void updateTurnData();

    QMqttClient::ClientState state() const;
    QMqttSubscription subscribe(const QString &topic);
    QMqttSubscription messageReceived(QMqttMessage &msg, QMqttTopicName &topic);

    QMqttSubscription unsubscribe(const QMqttTopicFilter &topic);
    //QMqttClient::publish(const QMqttTopicName &topic, const QByteArray &message = QByteArray(), quint8 qos = 0, bool retain = false);

signals:
    //sent when we are connected to the host
    void HostConnectionUpdate(QString msgStatus,QString state, const QString &hostname,
                              const quint16 port, const QString &id, const QString &appVersion, const QString &endpointToken);

public slots:
    void SendStatus(QString status,QByteArray &message);
    void SendStatus(QString status); //< Publish a new status

private slots:
    //void messageReceived(const QByteArray &message, const QMqttTopicName &topic);
    void messageReceived(const QByteArray &message, const QMqttTopicName &topic = QMqttTopicName());
    void handleStateChange();
    void brokerDisconnected();

private:
    QString         m_hostname;         //< the host to connect to
    quint16         m_port;             //< the port on the host to connect to
    QString         m_appVersion;       //< the version of the application to connect to
    QString         m_endpointToken;    //< the endpoint token on the host to connect to
    QMqttClient     *m_client;      //< the QMqttClient

    QString         m_deviceName;   //< A way to uniquely identify us
    QString         m_turnOnOff;
};

#endif // MQQTCLIENT_H
