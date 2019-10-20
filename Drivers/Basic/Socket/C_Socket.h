#ifndef C_SOCKET_H
#define C_SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

class C_Socket : public QObject
{
    Q_OBJECT
public:
    explicit C_Socket(QObject *parent = 0);
    
    void doConnect();

signals:
    // Closing the window
    void SIG_NewDataReceived(const QByteArray &data);

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    QTcpSocket *socket;
    
};

#endif // C_SOCKET_H
