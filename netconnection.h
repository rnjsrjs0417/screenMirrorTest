#ifndef NETCONNECTION_H
#define NETCONNECTION_H

#include <QtDebug>
#include <map>
#include <string>
#include <winsock2.h>
#include <windows.h>

class SecDialog;

class NetConnection
{
public:
    NetConnection(SecDialog* w, std::string server, void (SecDialog::*_callback)(int));
    ~NetConnection();

    bool init_network(std::string server);

    int get_devicecode();
    void cancel_code();
    int sendHealthData(int pulse, int max, int min, int spo2);

public:
    std::string id;
    std::string name;
    void thread_end();

private:
    void make_socket();
    void recv_thread();
    std::map<std::string, std::string> map_from_json(std::string str);
    std::map<std::string, std::string> http_request(std::string query);

private:
    SOCKET TCP_Socket;
    SOCKET HTTP_Socket;
    std::string server_url;
    SecDialog* window;
    void (SecDialog::*callback)(int);
};


#endif // NETCONNECTION_H
