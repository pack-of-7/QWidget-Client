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
#include <QBrush>
#include <QLinearGradient>
#include <QFont>
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

    seriesCo2 = new QLineSeries();
    seriesSweepGas = new QLineSeries();

    seriesCo2->setName("CO2 Removal");
    seriesSweepGas->setName("Sweep Gas Flow");

    dataWidget = new QWidget;
    chartWidget = new QWidget;

    chart = new QChart;
    chart->setAnimationOptions(QChart::SeriesAnimations);  // Set the animation effect when displaying
    chart->legend()->hide();
    chart->addSeries(seriesCo2);
    chart->addSeries(seriesSweepGas);
//    chart->setTitle("<span style=\"padding-bottom:20px; font-weight:bold; font-size:16px; color: #ffffff;\">Chart CO2 Removal, Sweep Gas Flow</span>");

    axisX = new QDateTimeAxis();
    axisY_1 = new QValueAxis();
    axisY_2  =new QValueAxis();

    axisX->setTickCount(8);
    axisX->setFormat("hh:mm:ss");

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

    axisY_1->setTickCount(8);
    axisY_2->setTickCount(8);

//    axisX->setTitleText("<span style=\"font-size:14px; margin:18px; color: #ffffff;\">Time</span>");
    axisY_1->setTitleText("<span style=\"font-size16:1px; margin:18px; color: #ffffff;\">CO2 Removal</span>");
    axisY_2->setTitleText("<span style=\"font-size16:1px; margin:18px; color: #ffffff;\">Sweep Gas Flow</span>");

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY_1,Qt::AlignLeft);
    chart->addAxis(axisY_2,Qt::AlignRight);

    seriesCo2->setPen(QPen(Qt::green,2,Qt::SolidLine));
    QPen linePenLimo;
//    QColor colorLimo;
//    colorLimo.setRgb(160,207,107); //#a0cf6b
    linePenLimo.setColor(QRgb(0xa0cf6b));//#a0cf6b
    linePenLimo.setWidth(2);
    seriesSweepGas->setPen(linePenLimo);

    seriesCo2->attachAxis(axisX);
    seriesCo2->attachAxis(axisY_1);

    seriesSweepGas->attachAxis(axisX);
    seriesSweepGas->attachAxis(axisY_2);

    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(QPointF(0, 0));
    backgroundGradient.setFinalStop(QPointF(0, 1));
    backgroundGradient.setColorAt(0.0, QRgb(0x056087));
    backgroundGradient.setColorAt(1.0, QRgb(0x0b1324));
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
//    chart->setBackgroundBrush(backgroundGradient);
    chart->setBackgroundVisible(false);

    // Customize axis label font
     QFont labelsFont;
     labelsFont.setPointSize(10);
     axisX->setLabelsFont(labelsFont);
     axisY_1->setLabelsFont(labelsFont);
     axisY_2->setLabelsFont(labelsFont);

     // Customize axis colors
     QPen axisPen(QRgb(0xffffff));
     axisPen.setWidth(2);
     axisX->setLinePen(axisPen);
     axisY_1->setLinePen(axisPen);
     axisY_2->setLinePen(axisPen);

     // Customize axis label colors
     QBrush axisBrush(Qt::white);
     axisX->setLabelsBrush(axisBrush);
     axisY_1->setLabelsBrush(axisBrush);
     axisY_2->setLabelsBrush(axisBrush);

     // Customize grid lines and shades
     axisX->setGridLineVisible(true);
     axisY_1->setGridLineVisible(true);
     axisY_2->setGridLineVisible(true);

//     axisY_1->setShadesPen(Qt::NoPen);
//     axisY_1->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
//     axisY_1->setShadesVisible(true);

//     axisY_2->setShadesPen(Qt::NoPen);
//     axisY_2->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
//     axisY_2->setShadesVisible(true);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  //Anti-aliasing rendering
    chartView->setAttribute( Qt::WA_TranslucentBackground, true );
    chartView->setFixedWidth(700);
    chartView->setFixedHeight(500);

    lblCo2 = new QLabel();
    lblCo2Data = new QLabel();
    lblSweepGas = new QLabel();
    lblSweepGasData = new QLabel();
    lblStatus = new QLabel();
    lblOnOff = new QLabel();

    lblCo2->setFixedHeight(30);
    lblCo2Data->setFixedHeight(80);
    lblSweepGas->setFixedHeight(30);
    lblSweepGasData->setFixedHeight(80);
    lblCo2->setFixedWidth(180);
    lblCo2Data->setFixedWidth(180);
    lblSweepGas->setFixedWidth(180);
    lblSweepGasData->setFixedWidth(180);
    lblStatus->setFixedHeight(20);
    lblOnOff->setFixedHeight(20);

    lblCo2->setText(QString("<div style='color:#ffffff; font-size:20px'>CO2 Removal</div>"));
    lblCo2->setAlignment(Qt::AlignCenter);
    lblCo2->setAttribute( Qt::WA_TranslucentBackground, true );
    lblCo2Data->setAttribute( Qt::WA_TranslucentBackground, true );
    lblSweepGas->setText(QString("<div style='color:#ffffff; background-color:transparent; font-size:20px'>Sweep Gas Flow</div>"));
    lblCo2Data->setAlignment(Qt::AlignCenter);
    lblSweepGas->setAlignment(Qt::AlignCenter);
    lblSweepGas->setAttribute( Qt::WA_TranslucentBackground, true );
    lblSweepGasData->setAlignment(Qt::AlignCenter);
    lblSweepGasData->setAttribute( Qt::WA_TranslucentBackground, true );
    lblStatus->setText(QString("<div style='color:#ffffff; font-size:20px'>Status:</div>"));
    lblStatus->setAttribute( Qt::WA_TranslucentBackground, true );
    lblOnOff->setAlignment(Qt::AlignLeft);
    lblOnOff->setAttribute( Qt::WA_TranslucentBackground, true );

    mainLayout = new QGridLayout;
    dataLayout = new QHBoxLayout;
    co2Layout = new QVBoxLayout;
    sweepGasLayout = new  QVBoxLayout;
    chartLayout = new QHBoxLayout;
    statusLayout = new QHBoxLayout;

    co2Layout->addWidget(lblCo2,Qt::AlignCenter);
    co2Layout->addWidget(lblCo2Data,Qt::AlignCenter);
    sweepGasLayout->addWidget(lblSweepGas);
    sweepGasLayout->addWidget(lblSweepGasData);
    dataLayout->addLayout(co2Layout);
    dataLayout->addSpacing(200);
    dataLayout->addLayout(sweepGasLayout);
    statusLayout->addWidget(lblStatus,Qt::AlignLeft);
    statusLayout->addWidget(lblOnOff,Qt::AlignLeft);
    chartLayout->setAlignment(chartView,Qt::AlignCenter);
    mainLayout->addLayout(dataLayout,1,0,Qt::AlignCenter);
    mainLayout->addWidget(chartView,2,0);
    //mainLayout->addLayout(statusLayout,3,0,Qt::AlignLeft);

    dataWidget->setLayout(mainLayout);

    m_wChart.setCentralWidget(dataWidget);
    //m_wChart.resize(700, 700);
    //m_wChart.setWindowTitle("Dashboard");
    m_wChart.setStyleSheet("* {color: qlineargradient(spread:pad, x0:1 x0:1, y1:1 y1:1, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"
                           "background: qlineargradient( x0:1 x0:1 , y1:1 y1:1, stop:0 #0b1324, stop:1 #056087);}");
    m_wChart.showFullScreen();

   //create Timer
    mTimer = new QTimer(this);

    // setup signal and slot
    connect(mTimer,SIGNAL(timeout()),SLOT(myTimerSlots()));


    if(t_mqttClient->m_OnOff!=QMqttClient::Connected)
    {
        lblOnOff->setText(QString("<div style='color:#ff0000; background-color:transparent; font-size:20px'>OFF</div>"));
    }



    if (t_mqttClient->state() != QMqttClient::Connected)
    {

        t_mqttClient->connectBroker();
        if(t_mqttClient->m_OnOff==QMqttClient::Connected)
        {
            lblOnOff->setText(QString("<div style='color:#ff0000; background-color:transparent; font-size:20px'>ON</div>"));
        }
        myTimerSlots();
    }else{
        lblOnOff->setText(QString("<div style='color:#ff0000; background-color:transparent; font-size:20px'>ON</div>"));
        myTimerSlots();
    }
        myTimerSlots();
         //msec
    mTimer->start(2000);
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
            //   qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    chart->axisX()->setMin(QDateTime::currentDateTime().addSecs(-40*1));
    chart->axisX()->setMax(QDateTime::currentDateTime().addSecs(0));
    if(seriesCo2->count()>219)
    {
        seriesCo2->removePoints(0,seriesCo2->count()-219);
    }

    if(seriesSweepGas->count()>219)
    {
        seriesSweepGas->removePoints(0,seriesSweepGas->count()-219);
    }

    seriesCo2->append(time,co2);

    lblCo2Data->setText(QString("<div align='center' style=' color:#00cd00; width:300px; font:bold; padding:20px; font-size:30px; background-color:transparent'>%1</div>").arg(co2));
    lblSweepGasData->setText(QString("<div align='center' style=' color:#a0cf6b; width:300px; font:bold; padding:20px; font-size:30px; background-color:transparent'>%1</div>").arg(sweepGas));
    qDebug() << time << ", " << co2;
    seriesSweepGas->append(QDateTime::currentDateTime().currentMSecsSinceEpoch(),sweepGas);

    qDebug() << sweepGas;

//    t_mqttClient->disconnectBroker();
}
