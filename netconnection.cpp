#include <unistd.h>
#include <cstdlib>
#include <netconnection.h>
#include <recvthread.h>
#include <secdialog.hpp>

#define HTTP_PORT 16002
#define TCP_PORT 16005
using namespace std;

char buffer[10000];
int i = 0 ;

NetConnection::NetConnection(SecDialog* w, string server, void (SecDialog::*_callback)(int)){
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
    closesocket(HTTP_Socket);
    WSACleanup();
}

void NetConnection::make_socket(){
    SOCKADDR_IN sock_sockAddr, http_SockAddr;
    struct hostent *host;

    HTTP_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    host = gethostbyname(server_url.c_str());

    http_SockAddr.sin_port=htons(HTTP_PORT);
    http_SockAddr.sin_family=AF_INET;
    http_SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

    if(connect(HTTP_Socket,(SOCKADDR*)(&http_SockAddr),sizeof(http_SockAddr)) != 0){
        qDebug() << "Could not connect HTTP server";
        return;
    }

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
    void(SecDialog::*pFunc)(int) = callback;

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
