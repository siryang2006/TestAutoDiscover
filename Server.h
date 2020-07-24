#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QUdpSocket>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

private:
    quint16 m_port = 6667;
    QUdpSocket *m_udpSocket = nullptr;
signals:

public slots:
    void receive();
};

#endif // SERVER_H
