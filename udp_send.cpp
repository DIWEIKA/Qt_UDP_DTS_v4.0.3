#include "udp_send.h"

udp_send::udp_send(MainWindow* _mainwindow):
    m_mainwindow(_mainwindow),
    sender(new QUdpSocket(this)),
    desAddress("192.168.0.10"),
    desPort(7),
    order("23")
{
    read_config();
}

void udp_send::read_config()
{
    QSettings *settings = new QSettings("C:/Qt_UDP_DTS/config.ini",QSettings::IniFormat);

    //Read
    settings->beginGroup("UDP_SEND");
    desAddress = settings->value("QHOSTADDRESS","").toString();
    desPort = settings->value("PORT",-1).toInt();
    order = settings->value("ORDER","").toString();
    settings->endGroup();
}

void udp_send::run()
{
    QByteArray m_send = order.toLatin1();

    int lenoSend = strlen(m_send);

    sender->writeDatagram(m_send.data(),lenoSend,QHostAddress(desAddress),desPort);

    qDebug()<<"Sender Order: " << m_send<<endl;
}


