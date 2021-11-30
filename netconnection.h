#ifndef NETCONNECTION_H
#define NETCONNECTION_H

#include <QObject>
#include <QtDebug>
#include <map>
#include <string>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>

class SecDialog;

class NetConnection : public QObject
{
    Q_OBJECT
public:
    NetConnection(SecDialog* w, std::string server);
    ~NetConnection();

    bool init_network(std::string server);

    int get_devicecode(void (SecDialog::*_callback)(int));
    int sendHealthData(int pulse, int max, int min, int spo2);
    void thread_end();
    void load_user(std::string mid, void (SecDialog::*_callback)(int));
    void new_load_user(std::string mid);

public slots:
    void ready2read();
    void ready2readCode();

public:
    std::string id;
    std::string name;

private:
    void make_socket();
    void recv_thread();
    std::map<std::string, std::string> map_from_json(std::string str);
    std::map<std::string, std::string> http_request(std::string query);

private:
    std::string server_url;
    SecDialog* window;
    QTcpSocket* socket;
    QNetworkReply * reply;
    QNetworkAccessManager* manager;
    void (SecDialog::*callback)(int);

};


#endif // NETCONNECTION_H
