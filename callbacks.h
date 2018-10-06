#pragma once
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include<memory>
#include<functional>

class Connection;
using ConnectionPtr = std::shared_ptr<Connection>;
using DataReceivedCbk = std::function<void (const ConnectionPtr, const bufferevent *bev)>; 
using AcceptCbk = std::function<void (ConnectionPtr conn)>;
