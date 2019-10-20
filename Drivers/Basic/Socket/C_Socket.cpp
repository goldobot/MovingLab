#include "C_Socket.h"

C_Socket::C_Socket(QObject *parent) :
    QObject(parent)
{
}

void C_Socket::doConnect()
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));

    qDebug() << "connecting...";

    // this is not blocking call
    socket->connectToHost("localhost", 50000);

    // we need to wait...
    if(!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
    }
}

void C_Socket::connected()
{
    qDebug() << "connected...";

    // Hey server, tell me about you.
    socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");
}

void C_Socket::disconnected()
{
    qDebug() << "disconnected...";
}

void C_Socket::bytesWritten(qint64 bytes)
{
    //qDebug() << bytes << " bytes written...";
}

void C_Socket::readyRead()
{
    //qDebug() << "reading...";

    // read the data from the socket
    //qDebug() << socket->readAll();

    QByteArray data = socket->readAll();
    emit SIG_NewDataReceived(data);
}
