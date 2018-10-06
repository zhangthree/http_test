#pragma once 
#include<event2/event.h>

class EventLoop {
 public:
    EventLoop();
    ~EventLoop();

    void Run();
        
    void Stop();

    event_base* GetBase() { return event_base_; }

 private:
    event_base* event_base_;    
};