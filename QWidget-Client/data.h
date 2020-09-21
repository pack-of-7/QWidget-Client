#ifndef DATA_H
#define DATA_H

#include <QtCore/QByteArray>
#include <QtCore/QStringList>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QJsonObject>
#include <QtCore/QJsonObject>

class Data : public QObject
{
     Q_OBJECT
     Q_PROPERTY(double batteryLevel READ batteryLevel WRITE setBatteryLevel NOTIFY batteryLevelChanged)
     Q_PROPERTY(int pressure READ pressure WRITE setPressure NOTIFY presureChanged)
     Q_PROPERTY(int co2 READ co2 WRITE setCo2 NOTIFY co2Changed)
     Q_PROPERTY(double temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)
     Q_PROPERTY(double humidity READ humidity WRITE setHumidity NOTIFY humidityChanged)
public:
    //enum ClassType {
      //  Warrior, Mage, Archer
    //};
   // Q_ENUM(ClassType)
     Data();
     Data(const int batteryLevel, int pressure, int co2, double temperature, double humidity);

        void read(const QJsonObject &json);
        void write(QJsonObject &json) const;

        void print(int indentation = 0) const;

       // void setBatteryLevel(const int &batLevel){
         //   if (batLevel != m_batteryLevel) {
           //     m_batteryLevel = batLevel;
             //   emit batteryLevelChanged();
             //}
        //}
        void setBatteryLevel(const double &batLevel){
            m_batteryLevel = batLevel;
        }
        int batteryLevel() const {
            return m_batteryLevel;
        }

        int pressure() const{
            return m_pressure;
        };
        void setPressure(int &press){
            m_pressure=press;
        }

        int co2() const{
            return m_co2;
        };
        void setCo2(int &co2){
            m_co2=co2;
        }

        int temperature() const{
            return m_temperature;
        };
        void setTemperature(double &temp){
            m_temperature=temp;
        }
        int humidity() const{
            return m_humidity;
        };
        void setHumidity(double &hum){
            m_humidity=hum;
        }

signals:
    void batteryLevelChanged();
    void presureChanged();
    void co2Changed();
    void temperatureChanged();
    void humidityChanged();

private:
   double m_batteryLevel;
   int m_pressure;
   int m_co2;
   double m_temperature;
   double m_humidity;
};

#endif // DATA_H
