QT       += core gui network mqtt

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MqttClient.cpp \
    data.cpp \
    main.cpp \
    mainwindow.cpp \
    mymultiserver.cpp \
    myserver.cpp \
    myserverthread.cpp \
    mythread.cpp \
    mythreadsobject.cpp \
    mytimer.cpp \
    threadsObject.cpp

HEADERS += \
    MqttClient.h \
    data.h \
    mainwindow.h \
    mymultiserver.h \
    myserver.h \
    myserverthread.h \
    mythread.h \
    mythreadsobject.h \
    mytimer.h \
    threadsObject.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#target.path = $$[QT_INSTALL_EXAMPLES]/mqtt/simpleclient
#INSTALLS += target

DISTFILES += \
    QWidget-Client-default.config
