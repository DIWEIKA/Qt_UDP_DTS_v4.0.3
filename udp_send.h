#ifndef UDP_SEND_H
#define UDP_SEND_H

//#include <WinSock2.h>
//#include <Windows.h>
#include <mainwindow.h>
#include <QThread>
#include "CirQueue.h"
#include <stdio.h>
#include <QUdpSocket>

class MainWindow;
class QUdpSocket;

class udp_send : public QThread
{
    Q_OBJECT

public:
    explicit udp_send(MainWindow* _mainwindow);

    MainWindow* m_mainwindow;

    QUdpSocket *sender;
    QString desAddress;
    int desPort;
    QString order;

    void read_config();

protected:
    void run();
};

#endif // UDP_SEND_H
