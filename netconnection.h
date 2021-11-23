#ifndef NETCONNECTION_H
#define NETCONNECTION_H

#include <QtDebug>
#include <map>
#include <string>
#include <winsock2.h>
#include <windows.h>

<<<<<<< HEAD
class SecDialog;
=======
class MainWindow;
>>>>>>> fbca8041db033b145428070811c624f39f4cb251

class NetConnection
{
public:
<<<<<<< HEAD
    NetConnection(SecDialog* w, std::string server, void (SecDialog::*_callback)(int));
=======
    NetConnection(MainWindow* w, std::string server, void (MainWindow::*_callback)(int));
>>>>>>> fbca8041db033b145428070811c624f39f4cb251
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
<<<<<<< HEAD
    SecDialog* window;
    void (SecDialog::*callback)(int);
=======
    MainWindow* window;
    void (MainWindow::*callback)(int);
>>>>>>> fbca8041db033b145428070811c624f39f4cb251
};


#endif // NETCONNECTION_H
