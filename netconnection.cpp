#include <unistd.h>
#include <cstdlib>
#include <netconnection.h>
#include <recvthread.h>
<<<<<<< HEAD
#include <secdialog.hpp>
=======
#include <mainwindow.h>
>>>>>>> fbca8041db033b145428070811c624f39f4cb251

#define TCP_PORT 16005
using namespace std;

char buffer[10000];
int i = 0 ;

<<<<<<< HEAD
NetConnection::NetConnection(SecDialog* w, string server, void (SecDialog::*_callback)(int)){
=======
NetConnection::NetConnection(MainWindow* w, string server, void (MainWindow::*_callback)(int)){
>>>>>>> fbca8041db033b145428070811c624f39f4cb251
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
        qDebug() << "WSAStartup failed.";
    }

    server_url = server;
    window = w;
    callback = _callback;
}

NetConnection::~NetConnection(){
    closesocket(TCP_Socket);
    WSACleanup();
}

void NetConnection::make_socket(){
    SOCKADDR_IN sock_sockAddr;
    struct hostent *host;
    TCP_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    host = gethostbyname(server_url.c_str());

    sock_sockAddr.sin_port=htons(TCP_PORT);
    sock_sockAddr.sin_family=AF_INET;
    sock_sockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

    if(connect(TCP_Socket,(SOCKADDR*)(&sock_sockAddr),sizeof(sock_sockAddr)) != 0){
        qDebug() << "Could not connect TCP server";
        return;
    }
}

void NetConnection::thread_end(){
<<<<<<< HEAD
    void(SecDialog::*pFunc)(int) = callback;
=======
    void(MainWindow::*pFunc)(int) = callback;
>>>>>>> fbca8041db033b145428070811c624f39f4cb251

    (window->*pFunc)(123);
}

int NetConnection::get_devicecode(){
    char b[] = "device";
    make_socket();
    send(TCP_Socket, b, strlen(b), 0);

    if(recv(TCP_Socket, buffer, sizeof(buffer), 0) <= 0){
        return -1;
    }

    RecvThread* rt = new RecvThread(this, &TCP_Socket);
    rt->start();

    return atoi(buffer);
}

void NetConnection::cancel_code(){
    closesocket(TCP_Socket);
}
