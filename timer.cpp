#include "timer.h"

#include <memory>

#define WAIT_FOR 1000

using namespace timer;

Timer::Timer()
    : status(NEVER_RUN)
    , mTime(std::chrono::duration<int> (std::chrono::seconds{ 5 }))
{
}

Timer::Timer(std::chrono::duration<int> ms)
    : status(NEVER_RUN)
    , mTime(ms)
{
}

ExitStatus Timer::run(const std::function<void(void)>& callback) {
    if ((status == FINISHED) && (mTimerThread->joinable())) {
        mTimerThread->join();
    }
    if (status == RUNNING) {
        stop();
    }
    if (mTimerThread != nullptr && mTimerThread->joinable()) {
        return IS_RUNNING;
    }
    mCallback = callback;
    status = RUNNING;
    mTimerThread = std::make_unique<std::thread>(&Timer::ticks, this);
    return SUCCESFULL_EXIT;
}

ExitStatus Timer::stop() {
    if (status == STOPPED) {
        return IS_STOPPED;
    }
    status = STOPPED;
    cv.notify_all();
    mTimerThread->join();
    return SUCCESFULL_EXIT;
}

void Timer::setTimer(std::chrono::duration<int> ms) {
    mTime = ms;
}

Timer::~Timer() {
    if (mTimerThread->joinable()) {
        mTimerThread->join();
    }
}

void Timer::ticks() {
    std::unique_lock<std::mutex> lk(cv_m);
    cv.wait_for(lk, mTime, [this](){return status != RUNNING;});
    if (status == RUNNING) {
        status = FINISHED;
        mCallback();
    }
}
