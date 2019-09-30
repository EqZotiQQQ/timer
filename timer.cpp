#include "timer.h"

#include <memory>

#define WAIT_FOR 1000

using namespace timer;

Timer::Timer()
    : status(NEVER_RUN)
    , mTime(std::chrono::milliseconds{ 5000 })
{
}

Timer::Timer(std::chrono::milliseconds ms)
    : status(NEVER_RUN)
    , mTime(ms)
{
}

Timer::Timer(int sec)
    : status(NEVER_RUN)
    , mTime(std::chrono::milliseconds{ sec * 1000 })
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
    mTimerThread->join();
    return SUCCESFULL_EXIT;
}

void Timer::setTimer(std::chrono::milliseconds ms) {
    mTime = ms;
}

void Timer::setTimer(int sec) {
    mTime = std::chrono::milliseconds{ sec * 1000 };
}

Timer::~Timer() {
    if (mTimerThread->joinable()) {
        mTimerThread->join();
    }
}

void Timer::ticks()
{
    while (status == RUNNING) {
        std::this_thread::sleep_for(mTime);
        status = FINISHED;
        mCallback();
    }

}
