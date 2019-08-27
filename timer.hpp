#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <atomic>

namespace timer{

#define WAIT_FOR 500

typedef std::atomic<bool> a_bool;
typedef std::chrono::milliseconds c_ms;

class Timer {
private:
    c_ms time;
    std::unique_ptr<std::thread> th;
    a_bool FLAG_FOR_TIMER{false};
private:
    void ticks();
public:
    Timer();
    int timerStart();
    int timerStop();
    int restartTimer();
    ~Timer();
};

}// namespace timer

#endif // TIMER_HPP
