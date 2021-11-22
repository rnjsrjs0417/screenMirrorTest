#ifndef RECVTHREAD_H
#define RECVTHREAD_H

#include <winsock2.h>
#include <netconnection.h>
#include <QThread>
#include <string>
#include <QtDebug>

class RecvThread : public QThread
{
public:
    RecvThread(NetConnection* n, SOCKET* s);
    void run();
    SOCKET* TCP_Socket;
private:
    NetConnection* net;
};

#endif // RECVTHREAD_H
