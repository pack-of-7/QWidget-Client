#include "MqttClient.h"


MqttClient::MqttClient(QObject *parent) :
    QObject (parent)
{
    m_client = new QMqttClient(this);

    // Create a Unique Device Name
    m_deviceName = QStringLiteral("%1-%2").arg(qAppName()).arg(QRandomGenerator::system()->generate() % 100000);

    qDebug() << m_deviceName;
    qDebug() << m_client;
    QString hostName="mqtt.cloud.kaaiot.com";
    int port = 1883;
    QString endpoint_token = "DY5oex7rC3";
    QString applications_version = "bt8h4h2ikfmg80udn370-1";

   // Connect the signals we need to process
    connect(m_client, &QMqttClient::stateChanged, this, &MqttClient::handleStateChange);
    connect(m_client, &QMqttClient::disconnected, this, &MqttClient::brokerDisconnected);
}

MqttClient::~MqttClient()
{

}

void MqttClient::connectBroker()
{
    m_client->connectToHost();
    qDebug() << "connectBrocker";
}

void MqttClient::disconnectBroker()
{
    m_client->disconnectFromHost();
}

QString MqttClient::hostname() const
{
    qDebug() << ":hostname() : " << m_hostname;
    return m_hostname;
}

void MqttClient::setHostname(const QString &hostname)
{
    m_hostname = hostname;
    m_client->setHostname(m_hostname);
}

quint16 MqttClient::port() const
{
    qDebug() << ":port() : "<< m_port;
    return m_port;
}

void MqttClient::setPort(quint16 port)
{
    m_port = port;
    qDebug() << "setPort: " << m_port;
    m_client->setPort(m_port);
}

QString MqttClient::endpointToken() const
{
    qDebug() << ":endpointToken(): " << m_endpointToken;
    return m_endpointToken;
}

void MqttClient::setEndpointToken(const QString &endpointToken)
{
    m_endpointToken=endpointToken;
}

void MqttClient::setAppVersion(const QString &appVersion)
{
    m_appVersion=appVersion;
}

void MqttClient::SendStatus(QString status,QByteArray &message)
{
    qDebug() << "SendStatus(QString status) " << status;

    if (m_client->state() == QMqttClient::Connected)
    {
        //kp1/application_version/dcx/endpoint_token/json/42/status
        messageReceived(message,status);
        m_client->publish(status,message);
        qDebug() << status;
        qDebug() << message;
    }
    else
    {
        qDebug() << "Broker is not connected!";
    }
}

void MqttClient::messageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    qDebug() << __FUNCTION__ << topic << ":" << message;
}


void MqttClient::handleStateChange()
{
    qDebug() << "handleStatechange";
    auto state = m_client->state();

    qDebug() << state ;

    // convert enum to text by brute force
    QString stateName;
    if (state == QMqttClient::Connected)
    {
        stateName = "Connected";
          qDebug()<< "state " << stateName;
    }
    else if (state == QMqttClient::Connecting)
    {
        stateName = "Connecting";
        qDebug()<<"state " << stateName;
    }
    else if (state == QMqttClient::Disconnected)
    {
        stateName = "Disconnected";
        qDebug() << "State "<< stateName ;
    }

    // emit the updated state
    emit HostConnectionUpdate(stateName, m_hostname, m_port, m_deviceName, m_appVersion, m_endpointToken);
}

void MqttClient::brokerDisconnected()
{
    handleStateChange();
    qDebug() << "brokerDisconnected()";

}

QString MqttClient::deviceName() const
{
    qDebug() << m_deviceName;
    return m_deviceName;
}

void MqttClient::setDeviceName(const QString &deviceName)
{
    m_deviceName = deviceName;
}

//QMqttSubscription MqttClient::subscribe(const QMqttTopicFilter &topic){
QMqttSubscription MqttClient::subscribe(const QString &topic){
    qDebug()<< "subscribe: " << topic;
    m_client->subscribe(topic);
    qDebug() << __FUNCTION__ << m_client->subscribe(topic)->Subscribed;
}

QMqttSubscription MqttClient::unsubscribe(const QMqttTopicFilter &topic){
    qDebug()<< "unsubscribe: " << topic;
    m_client->unsubscribe(topic);
}

QMqttClient::ClientState MqttClient::state() const
{
    return m_client->state();
}
