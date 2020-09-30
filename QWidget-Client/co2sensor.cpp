#include "co2sensor.h"
#include <QDebug>
#include <QTimer>


CO2Sensor::CO2Sensor(QObject *parent) :
    CO2SensorIF (parent)

{
    m_sendCO2Timer = new QTimer(this);

    // setup signal and slot
    connect(m_sendCO2Timer,SIGNAL(timeout()),this,SLOT(myTimerSlots()));

}
void CO2Sensor::myTimerSlots()
{

}
void CO2Sensor::sendDataSweepGas()
{

}
void CO2Sensor::sendDataCo2()
{

}
