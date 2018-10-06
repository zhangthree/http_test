#include <sys/socket.h>
#include <event2/util.h>
#include <memory.h>
#include "tcp_server.h"
#include "connection.h"

TcpServer::TcpServer(event_base* base, uint16_t port, uint32_t local_address) {
    base_ = base;
    port_ = port;
    local_address_ = local_address;
    nextConnId_ = 0;

    fd_ = ::socket(AF_INET, SOCK_STREAM, 0);
    evutil_make_socket_nonblocking(fd_);
}

TcpServer::~TcpServer() {

}

void TcpServer::AcceptCallback(evconnlistener *listener, evutil_socket_t fd,
                             sockaddr *addr, int socklen, void *context) {
    TcpServer* server = reinterpret_cast<TcpServer*>(context);
    server->OnAccept(fd);  
}

void TcpServer::Start() {
    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port_);
    sin.sin_addr.s_addr = htonl(local_address_);

    ::bind(fd_, (sockaddr*)&sin, sizeof(sockaddr_in));

    conn_ = evconnlistener_new(base_,AcceptCallback,this,LEV_OPT_CLOSE_ON_FREE,-1, fd_);
}

void TcpServer::OnAccept(int fd){
    ConnectionPtr conn(new Connection(fd));
    char buf[64];
    snprintf(buf, sizeof buf, "%d#%d", port_, nextConnId_);
    string name = buf;
    conns_[name] = conn;
    
    accept_cbk_(conn);
}