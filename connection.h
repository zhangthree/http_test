#pragma once 
#include <event2/event.h>
#include <event2/buffer.h>  
#include <event2/bufferevent.h>  

#include<functional>
#include<memory>
#include "callbacks.h"

class Connection : public std::enable_shared_from_this {
 public:
    Connection(event_base* base, int fd);
    ~Connection();

    void RegisterDataReceivedCallback(const DataReceivedCbk& cb) { dataCbk_ = cd;}
    void OnData();

 private:
    static void ReadCbk(bufferevent *bev, void *context);
    static void WriteCbk(bufferevent *bev, void *context);
    static void EventCbk(bufferevent *bev, short event, void *context);
 private:
    int fd_;
    DataReceivedCbk dataCbk_;
    event_base* base_;
    bufferevent *bev_;
}