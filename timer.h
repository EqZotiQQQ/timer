#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>
#include <chrono>
#include <thread>
#include <functional>
#include <condition_variable>

namespace timer{

enum TimerStatus{NEVER_RUN, FINISHED, STOPPED, RUNNING};
enum ExitStatus{IS_RUNNING = 2, IS_STOPPED = 1, SUCCESFULL_EXIT = 0};


class Timer {
private:
    TimerStatus status;
    std::chrono::milliseconds mTime;
    std::unique_ptr<std::thread> mTimerThread;
    std::function <void(void)> mCallback;
    std::condition_variable cv;
    std::mutex cv_m;
private:
    void ticks();
public:
    Timer();
    Timer(std::chrono::milliseconds ms);
    Timer(int sec);
    ExitStatus run(const std::function<void(void)> & callback);
    ExitStatus stop();
    void setTimer(std::chrono::milliseconds ms);
    void setTimer(int sec);
    ~Timer();
};

}// namespace timer

#endif // TIMER_H
