#include <unistd.h>
#include <cstdlib>
#include <netconnection.h>
#include <recvthread.h>
#include <secdialog.hpp>

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
    string q = "/validuser?id=" + mid;
    callback = _callback;

    string url = "http://" + server_url + q;
    qDebug() << url.c_str();
    QUrl serviceURL(url.c_str());
    QNetworkRequest request(serviceURL);

    reply = manager->get(request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(ready2read()));
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

    if(result){
        void(SecDialog::*pFunc)(int) = callback;

        (window->*pFunc)(123);
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

int NetConnection::sendHealthData(int pulse, int max, int min, int spo2){
    string q = "/addHealth?id=" + id + "&pulse=" + to_string(pulse) + "&max=" + to_string(max) + "&min=" + to_string(min) + "&spo2=" + to_string(spo2);

    map<string, string> res = http_request(q);
    if((*res.find("_result")).second == "T")
        if((*res.find("result")).second == "true") return 0;
    return 1;
}

map<string, string> NetConnection::http_request(string query){
    string get_http, website_HTML;
    map<string, string> ret;
    get_http = "GET " + query + " HTTP/1.1\r\nHost: " + server_url + ":" + to_string(HTTP_PORT) + "\r\nAccept: */*\r\n\r\n";

    send(HTTP_Socket,get_http.c_str(), strlen(get_http.c_str()),0 );

    int nDataLength, isKey = 2, go_loop = 1, space_after_col = 0;
    string headerkey, headerval, startline;
    map<string, string> header;
    while ((nDataLength = recv(HTTP_Socket,buffer,1,0)) > 0 && go_loop){
        char c = buffer[0];
        switch(c){
            case '\n': break;
            case '\r':
                if(isKey == 2){
                    startline = headerval;
                    headerval.clear();
                    isKey = 1;
                }
                else{
                    if(isKey == 1){
                        go_loop = 0;
                    }
                    else{
                        header.insert({headerkey, headerval});
                        headerkey.clear();
                        headerval.clear();
                        isKey = 1;
                    }
                }
            break;

            default:
                if(c >= 32){
                    if(c == ' ' && space_after_col){
                        space_after_col = 0;
                        break;
                    }
                    if(c == ':') {
                        if(isKey == 0) headerval += c;
                        else{
                            isKey = 0;
                            space_after_col = 1;
                        }
                    }
                    else if(isKey == 1){
                        headerkey += c;
                    }
                    else {
                        headerval += c;
                    }
                }
            break;
        }
    }

    int contentsize = 0, recvsize = 0;
    if(header.find("Content-Length") != header.end()){
        contentsize = stoi((*header.find("Content-Length")).second);
    }
    while (recvsize < contentsize && (nDataLength = recv(HTTP_Socket,buffer,contentsize,0)) > 0){
        website_HTML = buffer;
        recvsize += nDataLength;
    }

    if(header.find("Content-Type") != header.end()){
        ret = map_from_json(website_HTML);
        ret.insert({"_result", "T"});
    }
    else ret.insert({"_result", "F"});
    return ret;
}

map<string, string> NetConnection::map_from_json(string str){
    int str_size = str.size();
    int is_key = 1;
    string k, v;
    map<string, string> ret;
    for(int i = 1; i < str_size - 1; i++){
        if(str[i] == ':'){
            is_key = 1 - is_key;
            continue;
        }
        if(str[i] == '"') continue;
        if(str[i] == ','){
            ret.insert({k, v});
            k.clear();
            v.clear();
            continue;
        }
        if(is_key){
            k += str[i];
        }
        else{
            v += str[i];
        }
    }
    ret.insert({k, v});
    return ret;
}
