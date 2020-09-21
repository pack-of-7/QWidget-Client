#include "myserver.h"


MyServer::MyServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
    if(!server->listen(QHostAddress::Any,1234))
    {
        qDebug() << "Server could not start";
    }
    else
    {
        qDebug() << "server started";
    }
}

void MyServer::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    socket->write("hello client");
    socket->flush();
    socket->waitForBytesWritten(3000);
    socket->close();
}


