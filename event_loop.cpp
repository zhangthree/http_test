#include "event_loop.h"

EventLoop::EventLoop() {

    event_base_ = ::event_base_new();   
}

EventLoop::~EventLoop() {
    ::event_base_free(event_base_);
}

void EventLoop::Stop() {
    ::event_base_loopexit(event_base_, nullptr);
}

void EventLoop::Run() {
    ::event_base_dispatch(event_base_);
}

