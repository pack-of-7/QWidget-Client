#ifndef MYSERVERTHREAD_H
#define MYSERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QtDebug>
class MyServerThread : public QThread
{
    Q_OBJECT
public:
    explicit MyServerThread(int ID, QObject *parent = 0 );
    void run();

signals:
    void error(QTcpSocket::SocketError socketError);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    int socketDescription;
};

#endif // MYSERVERTHREAD_H
