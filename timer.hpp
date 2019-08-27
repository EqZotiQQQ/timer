#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <functional>
#include <chrono>
#include <thread>
#include <atomic>

namespace timer{


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
    int timerRestart();
    ~Timer();
};


}// namespace timer


#endif // TIMER_HPP
