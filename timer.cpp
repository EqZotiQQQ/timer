#include "timer.hpp"

#include <memory>

#define WAIT_FOR 100

using namespace timer;

Timer::Timer() {

}

int Timer::timerStart() {
    if(FLAG_FOR_TIMER == true) return 1;
    FLAG_FOR_TIMER.store(true);
    this->time = c_ms{ WAIT_FOR };
    th = std::make_unique<std::thread>(&Timer::ticks, this);
    return 0;
}

int Timer::timerStop() {
    if (FLAG_FOR_TIMER == false) return 1;
    FLAG_FOR_TIMER.store(false);
    th->join();
    return 0;
}

int Timer::timerRestart() {
    if (FLAG_FOR_TIMER == false) return 1;
    timerStop();
    timerStart();
    return 0;
}

Timer::~Timer() {
    if (th->joinable())
        th->join();
}

void Timer::ticks()
{
    int i {5};
    while (i > 0 && FLAG_FOR_TIMER.load()) {
        std::this_thread::sleep_for(time);
        --i;
        if(i == 0){
            if(th->joinable()){
                th->detach();
            }
            FLAG_FOR_TIMER.store(false);
        }
    }
}
