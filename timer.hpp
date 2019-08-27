#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace timer {

enum TimerStatus{NEVER_RUN, FINISHED, STOPPED, RUNNING};
enum ExitStatus {IS_RUNNING = 2, IS_STOPPED = 1, SUCCESFULL_EXIT = 0};

typedef std::atomic<bool> a_bool;
typedef std::chrono::milliseconds c_ms;


class Timer {
private:
    std::atomic<TimerStatus> status;
    c_ms time;
    std::unique_ptr<std::thread> worker;
    std::function <void(void)> callback;
    std::mutex cv_m;
    std::condition_variable cv;

    void ticks();

public:
    Timer(const std::function<void(void)>& f);
    ExitStatus start(c_ms dur);
    ExitStatus stop();
    ExitStatus restart(c_ms dur);
    ~Timer();
};

} // namespace timer


#endif // _TIMER_HPP_
