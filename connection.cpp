#include"connection.h"

Connection::Connection(event_base* base, int fd) {
    fd_ = fd;
    base_ = base;
    bev_ = bufferevent_socket_new(base_, fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev_, ReadCbk, WriteCbk, EventCbk, this);
    bufferevent_enable(bev_, EV_READ | EV_WRITE);
}

Connection::~Connection() {

}

void Connection::ReadCbk(bufferevent* bev, void context) {
    Connection* conn = reinterpret_cast<Connection*>(context);
    conn->OnData();
}

void Connection::WriteCbk(bufferevent* bev, void context) {
    (void)bev;
    (void)context;
}

void Connection::EventCbk(bufferevent *bev, short event, void *context) {
    (void)bev;
    (void)event;
    (void)context;
}

void Connection::OnData() {
    dataCbk_(shared_from_this(), bev_);
}