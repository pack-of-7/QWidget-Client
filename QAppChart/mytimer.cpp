#include "mytimer.h"

#include <QDebug>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsScene>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFrame>
#include <QDateTime>
#include <QDateTimeAxis>

MyTimer::MyTimer(QObject *parent) : QObject(parent)
{

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

    splSeriesCO2 = new QSplineSeries(chart);
    splSeriesSweepGas = new QSplineSeries(chart);
    splSeriesCO2->setName("CO2 Removal");
    splSeriesSweepGas->setName("Sweep Gas Flow");

    dataWidget = new QWidget;
    chartWidget = new QWidget;

    chart = new QChart;
    chart->setAnimationOptions(QChart::SeriesAnimations);  // Set the animation effect when displaying
    chart->legend()->hide();
    chart->setTitle("Chart CO2 Removal, Sweep Gas Flow");
    chart->addSeries(splSeriesCO2);
    chart->addSeries(splSeriesSweepGas);

    axisX = new QDateTimeAxis();
    axisY_1 = new QValueAxis();
    axisY_2  =new QValueAxis();

    axisX->setTickCount(8);
    axisX->setFormat("hh:mm:ss");
    axisX->setTitleText("Time");

    axisX->setMin(QDateTime::currentDateTime().addSecs(-40*1));
    axisX->setMax(QDateTime::currentDateTime().addSecs(0));

    //Datum:  QDateTime(2020-10-02 20:47:47.517 CEST Qt::LocalTime)
    qDebug()<< "Datum: " <<QDateTime::currentDateTime().addSecs(-40*1);

    //Datum:  QDateTime(2020-10-02 20:47:57.517 CEST Qt::LocalTime)
    qDebug()<< "Datum: " <<QDateTime::currentDateTime().addSecs(0);

    axisY_1->setMin(0);
    axisY_1->setMax(2100);

    axisY_2->setMin(0);
    axisY_2->setMax(2100);

    axisY_1->setTickCount(10);
    axisY_2->setTickCount(10);

    axisX->setTitleText("Time");
    axisY_1->setTitleText("CO2 Removal");
    axisY_2->setTitleText("Sweep Gas Flow");

    axisY_1->setLinePenColor(QColor(Qt::darkBlue));
    axisY_1->setGridLineColor(QColor(Qt::darkBlue));

    axisY_2->setLinePenColor(QColor(Qt::darkGreen));
    axisY_2->setGridLineColor(QColor(Qt::darkGreen));

    axisY_1->setGridLineVisible(false);
    axisY_2->setGridLineVisible(false);

    QPen penY1(Qt::darkBlue, 3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    QPen penY2(Qt::darkGreen,3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);

    axisY_1->setLinePen(penY1);
    axisY_2->setLinePen(penY2);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY_1,Qt::AlignLeft);
    chart->addAxis(axisY_2,Qt::AlignRight);

    splSeriesCO2->attachAxis(axisX);
    splSeriesCO2->attachAxis(axisY_1);

    splSeriesSweepGas->attachAxis(axisX);
    splSeriesSweepGas->attachAxis(axisY_2);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  //Anti-aliasing rendering

    chartView->setFixedWidth(700);
    chartView->setFixedHeight(500);
    chartView->setRenderHint(QPainter::SmoothPixmapTransform);

    lblCo2 = new QLabel("CO2 Removal");
    lblCo2Data = new QLabel();
    lblSweepGas = new QLabel("Sweep Gas Flow");
    lblSweepGasData = new QLabel();

    lblCo2->setFixedHeight(30);
    lblCo2Data->setFixedHeight(30);
    lblSweepGas->setFixedHeight(30);
    lblSweepGasData->setFixedHeight(30);
    lblCo2->setFixedWidth(150);
    lblCo2Data->setFixedWidth(150);
    lblSweepGas->setFixedWidth(150);
    lblSweepGasData->setFixedWidth(150);

    lblCo2->setFrameStyle(QFrame::NoFrame );
    lblCo2->setAlignment(Qt::AlignCenter);
    lblCo2Data->setFrameStyle(QFrame::NoFrame );
    lblCo2Data->setAlignment(Qt::AlignCenter);
    lblSweepGas->setAlignment(Qt::AlignCenter);
    lblSweepGasData->setAlignment(Qt::AlignCenter);

    mainLayout = new QGridLayout;
    dataLayout = new QHBoxLayout;
    co2Layout = new QVBoxLayout;
    sweepGasLayout = new  QVBoxLayout;
    chartLayout = new QHBoxLayout;

    co2Layout->addWidget(lblCo2,Qt::AlignCenter);
    co2Layout->addWidget(lblCo2Data,Qt::AlignCenter);
    sweepGasLayout->addWidget(lblSweepGas);
    sweepGasLayout->addWidget(lblSweepGasData);
    dataLayout->addLayout(co2Layout);
    dataLayout->addSpacing(200);
    dataLayout->addLayout(sweepGasLayout);

    chartLayout->setAlignment(chartView,Qt::AlignCenter);
    mainLayout->addLayout(dataLayout,1,0,Qt::AlignCenter);
    mainLayout->addWidget(chartView,2,0);

    dataWidget->setLayout(mainLayout);
    m_wChart.setCentralWidget(dataWidget);
    m_wChart.resize(700, 700);
    m_wChart.setWindowTitle("Dashboard");
    m_wChart.setStyleSheet("{color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                           "background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 cyan, stop:1 blue);}");
    m_wChart.show();

//   create Timer
    mTimer = new QTimer(this);

//   setup signal and slot
    connect(mTimer,SIGNAL(timeout()),SLOT(myTimerSlots()));

    if (t_mqttClient->state() != QMqttClient::Connected)
    {
        t_mqttClient->connectBroker();
        myTimerSlots();
    }else{
        myTimerSlots();
    }
    myTimerSlots();
        //msec
    mTimer->start(4000);
}

void MyTimer::myTimerSlots()
{
    qDebug()<< "timer ...";
    sendData();
}

void MyTimer::sendData()
{
    float co2 = (float)QRandomGenerator::global()->bounded(100, 2000);
    float sweepGas= (float)QRandomGenerator::global()->bounded(100, 2000);
    qDebug() << co2 << " " << sweepGas;

    QString json = QString("[{\"co2\":%1,\"pressure\":%2}]").arg(co2).arg(sweepGas);

    QByteArray baMessage=json.toUtf8();
    auto stateString =QString("kp1/%1/dcx/%2/json")
            .arg(qAppVersion)
            .arg(endpoint_token);
    qDebug() << baMessage;
    t_mqttClient->SendStatus(stateString,baMessage);

    QDateTime bjtime = QDateTime::currentDateTime();

    quint64 time = QDateTime::currentDateTime().currentMSecsSinceEpoch();

    qDebug()<< QDateTime::currentDateTime().currentSecsSinceEpoch()<< " " << time;

    chart->axisX()->setMin(QDateTime::currentDateTime().addSecs(-40*1));
    chart->axisX()->setMax(QDateTime::currentDateTime().addSecs(0));

    if(splSeriesCO2->count()>219)
    {
         splSeriesCO2->removePoints(0,splSeriesCO2->count()-219);
    }

    if(splSeriesSweepGas->count()>219)
    {
        splSeriesSweepGas->removePoints(0,splSeriesSweepGas->count()-219);
    }
    splSeriesCO2->append(time,co2);
    lblCo2Data->setText(QString("%1").arg(co2));
    lblSweepGasData->setText(QString("%1").arg(sweepGas));
    qDebug() << time << ", " << co2;
    splSeriesSweepGas->append(QDateTime::currentDateTime().currentMSecsSinceEpoch(),sweepGas);
    qDebug() << sweepGas;

  //t_mqttClient->disconnectBroker();
}
