#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

class Timer {
	std::atomic<bool> active{true};
	
    public:
        void setTimeout(void (*ptr)(), int delay);
        void setInterval(void (*ptr)(), int interval);
        void stop();

};

void Timer::setTimeout(void (*ptr)(), int delay) {
    active = true;
    std::thread t([=]() {
        if(!active.load()) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if(!active.load()) return;
        (*ptr) ();
        stop();
    });
    t.detach();
}

void Timer::setInterval(void (*ptr)(), int interval) {
    active = true;
    std::thread t([=]() {
        while(active.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            if(!active.load()) return;
            (*ptr) ();
        }
    });
    t.detach();
}

void Timer::stop() {
    active = false;
}
