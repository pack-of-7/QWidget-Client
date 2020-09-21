#include "data.h"


//Data::Data(QObject *parent):
  //  QObject (parent)
Data::Data()
{

}
void Data::read(const QJsonObject &json)
{
    if (json.contains("battery_level"))
        m_batteryLevel= json["battery_level"].toDouble();

    if (json.contains("pressure"))
        m_pressure= json["pressure"].toInt();

    if (json.contains("temperature"))
        m_temperature = json["temperature"].toDouble();
    if (json.contains("co2"))
        m_co2= json["co2"].toInt();
    if (json.contains("humidity"))
        m_humidity= json["humidity"].toDouble();
}

void Data::write(QJsonObject &json) const
{
    json["battery_level"] = m_batteryLevel;
    json["pressure"] = m_pressure;
    json["temperature"] = m_temperature;
    json["co2"]=m_co2;
}


//QJsonObject::iterator 	insert(const QString &key, const QJsonValue &value)
