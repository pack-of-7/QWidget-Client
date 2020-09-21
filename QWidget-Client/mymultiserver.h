#ifndef MYMULTISERVER_H
#define MYMULTISERVER_H

#include "myserverthread.h"

#include <QTcpServer>
#include <QDebug>

class MyMultiServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyMultiServer(QObject *parent =0 );
    void startServer();
signals:
public slots:

protected:
    void incomingConnection(int socketDescriptior);



};

#endif // MYMULTISERVER_H
