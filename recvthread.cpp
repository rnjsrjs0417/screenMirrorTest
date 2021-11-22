#include "recvthread.h"

RecvThread::RecvThread(NetConnection* n, SOCKET* s)
{
    net = n;
    TCP_Socket = s;
}

void RecvThread::run(){
    int is_id = 1;
    std::string id, name;
    char buffer[500];
    while(recv(*TCP_Socket,buffer, 1,0) > 0){
        if(buffer[0] == '\n'){
            if(is_id == 1) {
                is_id = 0;
            }
            else {
                break;
            }
            continue;
        }
        if(is_id == 1) id += buffer[0];
        else name += buffer[0];
    }
    net->id = id;
    net->name = name;
    net->thread_end();
}
