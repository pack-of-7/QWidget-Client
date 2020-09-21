#include "mymultiserver.h"
#include <QTcpSocket>
MyMultiServer::MyMultiServer(QObject *parent) : QTcpServer(parent)
{

}
void MyMultiServer::startServer(){

    if(!this->listen(QHostAddress::Any,1234))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening..";
    }
}
void MyMultiServer::incomingConnection(int socketDescriptior)
{
    qDebug() << socketDescriptior << "Connecting..";
    MyServerThread *serverThread = new MyServerThread(socketDescriptior,this);
    connect(serverThread,SIGNAL(finished()),serverThread, SLOT(deleteLater()));
    serverThread->start();
}
