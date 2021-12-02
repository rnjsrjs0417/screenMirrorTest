#ifndef NETCONNECTION_H
#define NETCONNECTION_H

#include <QObject>
#include <QtDebug>
#include <vector>
#include <string>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class SecDialog;
class MainWindow;

class NetConnection : public QObject
{
    Q_OBJECT
public:
    NetConnection(MainWindow* w, std::string server);
    ~NetConnection();

    bool init_network(std::string server);

    int get_devicecode(void (MainWindow::*_callback)(int));
    int sendHealthData(int pulse, int max, int min, int spo2);
    void thread_end();
    void load_user(std::string mid, void (MainWindow::*_callback)(int));
    void new_load_user(std::string mid);
    void get_todo(SecDialog* w, void (SecDialog::*_callback)(int));
    void get_weather(SecDialog* w, void (SecDialog::*_callback)(int));

public slots:
    void ready2read();
    void ready2readCode();
    void readytodo();
    void readyweather();

public:
    std::string id;
    std::string name;
    std::vector<std::string> todo;
    std::string server_url;
    double temp = 0;
    double humidity = 0;
    int rain = 0;

private:
    void make_socket();
    void recv_thread();
    std::map<std::string, std::string> map_from_json(std::string str);
    std::map<std::string, std::string> http_request(std::string query);

private:
    MainWindow* window;
    SecDialog* mainwindow;
    QTcpSocket* socket;
    QNetworkReply * reply;
    QNetworkAccessManager* manager;
    void (MainWindow::*callback)(int);
    void (SecDialog::*maincallback)(int);

};


#endif // NETCONNECTION_H
