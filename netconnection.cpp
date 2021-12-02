#include <unistd.h>
#include <cstdlib>
#include <netconnection.h>
#include <recvthread.h>
#include <secdialog.hpp>
#include <mainwindow.h>

#define HTTP_PORT 16002
#define TCP_PORT 16005
using namespace std;

int i = 0 ;

NetConnection::NetConnection(SecDialog* w, string server) : QObject(w){
    manager = new QNetworkAccessManager(this);
    server_url = server;
    window = w;
}

NetConnection::~NetConnection(){
}

void NetConnection::thread_end(){
    void(SecDialog::*pFunc)(int) = callback;

    (window->*pFunc)(123);
}

int NetConnection::get_devicecode(void (SecDialog::*_callback)(int)){
    char b[] = "device";
    callback = _callback;

    socket = new QTcpSocket(this);
    socket->connectToHost(server_url.c_str(), 16005);
    socket->waitForConnected();
    socket->write("device");
    socket->waitForReadyRead(30000);

    QString str(socket->readAll());

    connect(socket, SIGNAL(readyRead()), this, SLOT(ready2readCode()));

    return atoi(str.toStdString().c_str());
}

void NetConnection::load_user(string mid, void (SecDialog::*_callback)(int)){
    string q = ":16002/validuser?id=" + mid;
    callback = _callback;

    string url = "http://" + server_url + q;
    qDebug() << url.c_str();
    QUrl serviceURL(url.c_str());
    QNetworkRequest request(serviceURL);

    reply = manager->get(request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(ready2read()));
}

void NetConnection::get_todo(MainWindow* w, void (MainWindow::*_callback)(int)){
    string q = ":16002/getTodo?id=dmsrn135";
    //string q = "/getTodo?id=" + id;
    maincallback = _callback;
    mainwindow = w;
    string url = "http://" + server_url + q;
    QUrl serviceURL(url.c_str());
    QNetworkRequest request(serviceURL);

    qDebug() << url.c_str();
    reply = manager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(readytodo()));
}

int NetConnection::sendHealthData(int pulse, int max, int min, int spo2){
    string q = ":16002/addHealth?id=" + id + "&pulse=" + to_string(pulse) + "&max=" + to_string(max) + "&min=" + to_string(min) + "&spo2=" + to_string(spo2);

    string url = "http://" + server_url + q;

    QUrl serviceURL(url.c_str());
    QNetworkRequest request(serviceURL);

    reply = manager->get(request);
    return 0;
}

void NetConnection::new_load_user(string str){
    manager = new QNetworkAccessManager(this);

    string url = server_url + str;
    QUrl serviceURL(url.c_str());
    QNetworkRequest request(serviceURL);

    reply = manager->get(request);

}

void NetConnection::ready2read(){
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QJsonObject object = document.object();

    auto value = object.value("result");
    bool result = value.toBool();

    void(SecDialog::*pFunc)(int) = callback;
    if(result){
        (window->*pFunc)(0);
    }
    else{
        (window->*pFunc)(-1);
    }
//    QJsonValue value = object.value("agentsArray");
//    QJsonArray array = value.toArray();
}

void NetConnection::ready2readCode(){
    QString data_ = socket->readAll();
    string data = data_.toStdString();
    int is_id = 1;
    string id_temp, name_temp;
    if(data.size() == 0) return;
    for(int i = 0; i < data.size(); i++){
        if(data[i] == '\n'){
            if(is_id == 1) {
                is_id = 0;
            }
            else {
                break;
            }
            continue;
        }
        if(is_id == 1) id_temp += data[i];
        else name_temp += data[i];
    }
    id = id_temp;
    name = name_temp;

    qDebug() << id.c_str() << name.c_str();

    thread_end();
}

void NetConnection::readytodo(){
    qDebug() << "test";
    auto ret = reply->readAll();
    qDebug() << ret;
    QJsonDocument document = QJsonDocument::fromJson(ret);
    QJsonObject object = document.object();

    auto value = object.value("result");
    auto result = value.toArray();

    todo.clear();
    qDebug() << result.size();
    for(auto i = 0; i < result.size(); i++){
       qDebug() << result.at(i);
    }

    void(MainWindow::*pFunc)(int) = maincallback;
    (mainwindow->*pFunc)(123);
//    QJsonValue value = object.value("agentsArray");
//    QJsonArray array = value.toArray();
}
