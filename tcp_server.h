#pragma once
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>

#include<stdint.h>
#include<unordered_map>
#include<string>
#include<memory>

#include "connection.h"
#include "callbacks.h"
using std::string;

using ConnMap = std::unordered_map<string, ConnectionPtr>;

class TcpServer {
 public:
    TcpServer(event_base* base, uint16_t port, uint32_t local_address);
    ~TcpServer();

    void RegisterAcceptCbk(const AcceptCbk& cbk) { accept_cbk = cbk; }

    void Start();

 private:
    static void AcceptCallback(evconnlistener *listener, evutil_socket_t fd,
                             sockaddr *addr, int socklen, void *context);

    void OnAccept(int fd);
 private:
    event_base* base_;
    evconnlistener *conn_;
    int fd_;
    uint16_t port_;
    uint32_t local_address_;
    uin32_t nextConnId_;
    AcceptCbk accept_cbk_;
    ConnMap conns_;    

}