#ifndef NETCONNECTION_H
#define NETCONNECTION_H

#include <QtDebug>
#include <map>
#include <string>
#include <winsock2.h>
#include <windows.h>

class MainWindow;

class NetConnection
{
public:
    NetConnection(MainWindow* w, std::string server, void (MainWindow::*_callback)(int));
    ~NetConnection();

    bool init_network(std::string server);

    int get_devicecode();
    void cancel_code();

public:
    std::string id;
    std::string name;
    void thread_end();

private:
    void make_socket();
    void recv_thread();

private:
    SOCKET TCP_Socket;
    std::string server_url;
    MainWindow* window;
    void (MainWindow::*callback)(int);
};


#endif // NETCONNECTION_H
