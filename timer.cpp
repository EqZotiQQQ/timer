#include "timer.hpp"

#include <memory>

#include <iostream>
using namespace std;

#define WAIT_FOR 100

using namespace timer;


Timer::Timer():status(NEVER_RUN) {

}

ExitStatus Timer::timerStart(const std::function<void(void)>& f) {
    if((status == FINISHED) && th->joinable()) {
        th->join();
    }
    if(FLAG_FOR_TIMER == true || (th != nullptr && th->joinable())) {
        return IS_RUNNING;
    }
    runFunction = f;
    FLAG_FOR_TIMER.store(true);
    status = RUNNING;
    this->time = c_ms{ WAIT_FOR };
    th = std::make_unique<std::thread>(&Timer::ticks, this);
    return SUCCESFULL_EXIT;
}

ExitStatus Timer::timerStop() {
    if (FLAG_FOR_TIMER == false) {
        return IS_STOPPED;
    }
    status = STOPPED;
    FLAG_FOR_TIMER.store(false);
    th->join();
    return SUCCESFULL_EXIT;
}

ExitStatus Timer::timerRestart(const std::function<void(void)>& f) {
    if (FLAG_FOR_TIMER == false) {
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
    while (i > 0 && status == RUNNING) {
        std::this_thread::sleep_for(time);
        --i;
        if(i == 0) {
            status = FINISHED;
            FLAG_FOR_TIMER.store(false);
            runFunction();
        }
    }
}
