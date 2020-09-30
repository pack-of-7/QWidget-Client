#include "co2sensor.h"
#include <QDebug>
#include <QTimer>


CO2Sensor::CO2Sensor(QObject *parent) :
    CO2SensorIF (parent)

{
    m_sendCO2Timer = new QTimer(this);

    // setup signal and slot
    connect(m_sendCO2Timer,SIGNAL(timeout()),this,SLOT(myTimerSlots()));
    t_settings = new QSettings();
    qHostname = t_settings->value("mqtt/broker", hostName).toString();
    qPort    = t_settings->value("mqtt/port", port).toInt();
    qAppVersion=t_settings->value("mqtt/applicationsVersion",applications_version).toString();
    qEndpointToken=t_settings->value("mqtt/endpointToken",endpoint_token).toString();

    t_mqttClient = new MqttClient(this);
    t_mqttClient->setPort(qPort);
    t_mqttClient->setHostname(qHostname);
    t_mqttClient->setEndpointToken(qEndpointToken);
    t_mqttClient->setAppVersion(qAppVersion);
    t_settings->sync();

    qDebug() << qPort<<" "<< qHostname<< " " << qEndpointToken << " " << qAppVersion;

    if (t_mqttClient->state() != QMqttClient::Connected)
   {
    t_mqttClient->connectBroker();
        qDebug()<< "if";
        myTimerSlots();
    }else{
        qDebug()<< "else";
         myTimerSlots();
    }
   // myTimerSlots();

    //msec
   // m_sendCO2Timer.start(6000);

    m_sendCO2Timer->setInterval(4000);
    //m_sendCO2Timer->setSingleShot(false);

    m_sendCO2Timer->start();
}
void CO2Sensor::myTimerSlots()
{
    qDebug()<< "timer CO2Sensor...";
    sendDataCo2();
    sendDataSweepGas();
}
void CO2Sensor::sendDataSweepGas()
{
//    qDebug() << "sendDataSweepGas";
//    double temp= (double)QRandomGenerator::global()->bounded(-50, 45);
//    double humidity= (double)QRandomGenerator::global()->bounded(0, 100);
//   // float co2 =(float)QRandomGenerator::global()->bounded(100, 1000);
//    double battery_level= (double)QRandomGenerator::global()->bounded(0, 1000);
//    float pressure= (float)QRandomGenerator::global()->bounded(100, 2000);
//    qDebug() << temp << " " << humidity << " " << battery_level<< " " << pressure;
//   // QString json = QString("[{\"temperature\":%1,\"humidity\": %2,\"co2\":%3,\"battery_level\": %4,\"pressure\":%5}]"
//    QString json = QString("[{\"temperature\":%1,\"humidity\": %2,\"battery_level\": %3,\"pressure\":%4}]")
//           .arg(temp)
//           .arg(humidity)
//       //    .arg(co2)
//           .arg(battery_level)
//           .arg(pressure);

// //        QString json1="[{\"temperature\":30,\"humidity\": 63,\"co2\":500,\"battery_level\": 85.7,\"pressure\":400}]";

//    QByteArray baMessage=json.toUtf8();
//    auto stateString =QString("kp1/%1/dcx/%2/json")
//            .arg(qAppVersion)
//            .arg(endpoint_token);
//    qDebug() << baMessage;
//    t_mqttClient->SendStatus(stateString,baMessage);

//        QDateTime now = QDateTime::currentDateTime();
//        qDebug()<< "data " << now;
//        //m_lastCO2 = co2;
//        m_lastSweepGas = pressure;
//        // create a temp change of -4 to 5 based on the time
//       // float change = static_cast<float>((now.toSecsSinceEpoch() % 11) - 5);
//       // qDebug() << "change "<< change;
//        //m_lastCO2 += change;
//       // qDebug() << "m_lastCO2 : " <<m_lastCO2 ;
//        qDebug() << " m_lastSweepGas : " << m_lastSweepGas ;

//        //emit newCO2(now, m_lastCO2);
//        emit newSweepGas(now, m_lastSweepGas);


//    //t_mqttClient->disconnectBroker();
}
void CO2Sensor::sendDataCo2()
{
//    double temp= (double)QRandomGenerator::global()->bounded(-50, 45);
//    double humidity= (double)QRandomGenerator::global()->bounded(0, 100);
//    float co2 =(float)QRandomGenerator::global()->bounded(100, 1000);
//    double battery_level= (double)QRandomGenerator::global()->bounded(0, 1000);
//   // float pressure= (float)QRandomGenerator::global()->bounded(100, 2000);
//    qDebug() << temp << " " << humidity << " " << co2 << " " << battery_level;
////    QString json = QString("[{\"temperature\":%1,\"humidity\": %2,\"co2\":%3,\"battery_level\": %4,\"pressure\":%5}]")
//      QString json = QString("[{\"temperature\":%1,\"humidity\": %2,\"co2\":%3,\"battery_level\": %4}]")
//           .arg(temp)
//           .arg(humidity)
//           .arg(co2)
//           .arg(battery_level);
//          // .arg(pressure);
// //        QString json1="[{\"temperature\":30,\"humidity\": 63,\"co2\":500,\"battery_level\": 85.7,\"pressure\":400}]";

//    QByteArray baMessage=json.toUtf8();
//    auto stateString =QString("kp1/%1/dcx/%2/json")
//            .arg(qAppVersion)
//            .arg(endpoint_token);
//    qDebug() << baMessage;
//    t_mqttClient->SendStatus(stateString,baMessage);

//        QDateTime now = QDateTime::currentDateTime();
//        qDebug()<< "data " << now;
//        m_lastCO2 = co2;
//     //   m_lastSweepGas = pressure;
//        // create a temp change of -4 to 5 based on the time
//       // float change = static_cast<float>((now.toSecsSinceEpoch() % 11) - 5);
//       // qDebug() << "change "<< change;
//        //m_lastCO2 += change;
//        qDebug() << "m_lastCO2 : " <<m_lastCO2 ;
//        //qDebug() << " m_lastSweepGas : " << m_lastSweepGas ;

//        emit newCO2(now, m_lastCO2);
//        //emit newSweepGas(now, m_lastSweepGas);


//    //t_mqttClient->disconnectBroker();
}
