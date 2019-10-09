#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>
#include <chrono>
#include <thread>
#include <functional>
#include <condition_variable>

namespace timer{

enum TimerStatus{NEVER_RUN, FINISHED, STOPPED, RUNNING};

class Timer {
private:
    TimerStatus status;
    std::unique_ptr<std::thread> mTimerThread;
    std::chrono::duration<int> mTime;
    std::function <void(void)> mCallback;
    std::condition_variable cv;
    std::mutex cv_m;
private:
    void ticks();
public:
    Timer();
    Timer(std::chrono::duration<int> mTime);
    void run(const std::function<void(void)> & callback);
    void stop();
    void setTimer(std::chrono::duration<int> mTime);
    ~Timer();
};

}// namespace timer

#endif // TIMER_H
