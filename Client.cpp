#include "Client.h"
#include <QTimer>
#include <QNetworkInterface>

QStringList getHostIpAddress()
{
    QStringList strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
           if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
               ipAddressesList.at(i).toIPv4Address()) {
               strIpAddress.push_back(ipAddressesList.at(i).toString());
           }
     }
     // 如果没有找到，则以本地IP地址为IP
     if (strIpAddress.isEmpty())
        strIpAddress.push_back(QHostAddress(QHostAddress::LocalHost).toString());
     return strIpAddress;
}

Client::Client(QObject* parent)
    : QObject(parent)
{
    m_pUdpClient = new QUdpSocket(this);
    m_pUdpClient->bind(m_port, QUdpSocket::ShareAddress);

    connect(m_pUdpClient, &QUdpSocket::readyRead, this, [=]() {
        while (m_pUdpClient->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(m_pUdpClient->pendingDatagramSize());
            m_pUdpClient->readDatagram(datagram.data(),datagram.size());
        }
    });

    startTimer(1000);
}

void Client::timerEvent(QTimerEvent *event)
{
    QString msg = getHostIpAddress().join(",");
    m_pUdpClient->writeDatagram(msg.toLatin1(), msg.length(), QHostAddress("255.255.0.0")/*QHostAddress::Broadcast*/, m_port);
}
