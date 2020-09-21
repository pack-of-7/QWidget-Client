#include "myserverthread.h"

MyServerThread::MyServerThread(int ID, QObject *parent):
    QThread(parent)
{
    this->socketDescription = ID;
}
void MyServerThread::run()
{
     qDebug() <<socketDescription << "Starting Thread";
     socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socketDescription))
    {
        emit error(socket->error());
        return;
    }

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconected()),Qt::DirectConnection);

    qDebug() <<socketDescription << "client Connected";

    exec();
}

void MyServerThread::readyRead()
{
    QByteArray Data = socket->readAll();
    qDebug() <<socketDescription << "Data in: ";
    socket->write(Data);
}

void MyServerThread :: disconnected()
{
    socket->deleteLater();
    exit(0);
}
