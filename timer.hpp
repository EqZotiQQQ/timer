#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <functional>
#include <chrono>
#include <thread>
#include <functional>
namespace timer{

enum TimerStatus{NEVER_RUN, FINISHED, STOPPED, RUNNING};
enum ExitStatus{IS_RUNNING = 2, IS_STOPPED = 1, SUCCESFULL_EXIT = 0};

typedef std::chrono::milliseconds c_ms;


class Timer {
private:
    TimerStatus status;
    c_ms time;
    std::unique_ptr<std::thread> th;
    std::function <void(void)> runFunction;
private:
    void ticks();
public:
    Timer();
    ExitStatus timerStart(const std::function<void(void)>& f);
    ExitStatus timerStop();
    ExitStatus timerRestart(const std::function<void(void)>& f);
    ~Timer();
};


}// namespace timer


#endif // TIMER_HPP
