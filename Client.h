#ifndef CLIENT_H
#define CLIENT_H

#include <QUdpSocket>
#include <QObject>

class Client : public QObject
{
    Q_OBJECT

public:
    Client(QObject* parent=nullptr);

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    QUdpSocket *m_pUdpClient = nullptr;
    quint16 m_port = 6667;
};

#endif // CLIENT_H
