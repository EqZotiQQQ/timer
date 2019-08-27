#include "timer.hpp"

#include <memory>

#define WAIT_FOR 100

using namespace timer;

Timer::Timer():status(NEVER_RUN) {

}

ExitStatus Timer::timerStart(const std::function<void(void)>& f) {
    if( (status == FINISHED) && (th->joinable()) ) {
        th->join();
    }
    if( (status == RUNNING) || (th != nullptr && th->joinable()) ) {
        return IS_RUNNING;
    }
    runFunction = f;
    status = RUNNING;
    this->time = c_ms{ WAIT_FOR };
    th = std::make_unique<std::thread>(&Timer::ticks, this);
    return SUCCESFULL_EXIT;
}

ExitStatus Timer::timerStop() {
    if (status == STOPPED) {
        return IS_STOPPED;
    }
    status = STOPPED;
    th->join();
    return SUCCESFULL_EXIT;
}

ExitStatus Timer::timerRestart(const std::function<void(void)>& f) {
    if (STOPPED == false) {
        return IS_STOPPED;
    }
    timerStop();
    timerStart(f);
    return SUCCESFULL_EXIT;
}

Timer::~Timer() {
    if (th->joinable()) {
        th->join();
    }
}

void Timer::ticks()
{
    int i {5};
    while ( (i > 0) && (status == RUNNING) ) {
        std::this_thread::sleep_for(time);
        --i;
        if(i == 0) {
            status = FINISHED;
            runFunction();
        }
    }
}
