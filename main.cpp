#include <QCoreApplication>
#include <QUdpSocket>
#include <QHostInfo>
#include "Client.h"
#include "Server.h"

void getNetworkIps() {
    for(int i = 1 ; i < 256; i++) {
        for (int j=1; j<256; j++) {
            QHostInfo::lookupHost(QString("10.201.%1.%2").arg(i).arg(j), [](QHostInfo info){
                qDebug()<<info.errorString()<<info.hostName()<<info.addresses()<<endl;
            });
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    getNetworkIps();
    Server s;
    Client c;

    return a.exec();
}
