#include "Server.h"
#include <QDebug>

Server::Server(QObject *parent) : QObject(parent)
{
    m_udpSocket = new QUdpSocket(this);
    QHostAddress addr("0.0.0.0");
    m_udpSocket->bind(addr, m_port);
    connect(m_udpSocket, SIGNAL(readyRead()), this, SLOT(receive()));
}

void Server::receive()
{
    QByteArray ba;
    while (m_udpSocket->hasPendingDatagrams())
    {
        ba.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->readDatagram(ba.data(), ba.size());
        qDebug() << ba.data() << endl;
    }
}
