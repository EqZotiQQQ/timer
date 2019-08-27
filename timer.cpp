#include "timer.hpp"

#include <memory>
#include <iostream>

using namespace std;
using namespace timer;

Timer::Timer(const std::function<void(void)>& f)
    : status(NEVER_RUN)
    , callback(f) {}

ExitStatus Timer::start(c_ms dur) {
    if ((status == FINISHED) && worker->joinable()) {
        worker->join();
    }
    if (status == RUNNING || (worker != nullptr && worker->joinable())) {
        return IS_RUNNING;
    }
    status = RUNNING;
    this->time = dur;
    worker = std::make_unique<std::thread>(&Timer::ticks, this);
    return SUCCESFULL_EXIT;
}

ExitStatus Timer::stop() {
    if (status != RUNNING) {
        return IS_STOPPED;
    }
    status = STOPPED;
    cv.notify_all();
    worker->join();
    return SUCCESFULL_EXIT;
}

ExitStatus Timer::restart(c_ms dur) {
    if (status != RUNNING) {
        return IS_STOPPED;
    }
    this->stop();
    this->start(dur);
    return SUCCESFULL_EXIT;
}

Timer::~Timer() {
    this->stop();
    if (worker->joinable()) {
        worker->join();
    }
}

void Timer::ticks()
{
    unique_lock<mutex> lk(cv_m);
    cv.wait_for(lk, time, [this]{return status != RUNNING;});
    if (status == RUNNING) {
        callback();
        status = FINISHED;
    }
}
