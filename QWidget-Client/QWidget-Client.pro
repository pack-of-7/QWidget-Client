QT       += core gui network mqtt charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quick quickwidgets
TEMPLATE = app
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    co2sensor.cpp \
    co2sensorif.cpp \
    main.cpp \
    mainwindow.cpp \
    mqttclient.cpp

HEADERS += \
    co2sensor.h \
    co2sensorif.h \
    mainwindow.h \
    mqttclient.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#target.path = $$[QT_INSTALL_EXAMPLES]/mqtt/simpleclient
#INSTALLS += target

DISTFILES += \
    Chart.qml \
    QWidget-Client-default.config

RESOURCES += \
    qml-chart.qrc
