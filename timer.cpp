#include "timer.hpp"


#include <memory>
#include <iostream>


#define WAIT_FOR 500


using namespace timer;
using std::cout;
using std::endl;

Timer::Timer() {

}

int Timer::timerStart() {
    if(FLAG_FOR_TIMER == true) return 1;  cout << "timer start" << endl;
    FLAG_FOR_TIMER.store(true);           cout << "timer start store true" << endl;
    this->time = c_ms{ WAIT_FOR };        cout << "timer start before make_unique" << endl;
    th = std::make_unique<std::thread>(&Timer::ticks, this); cout << "after make_unique" << endl;
    return 0;
}

int Timer::timerStop() {

    if (FLAG_FOR_TIMER == false) return 1;

    FLAG_FOR_TIMER.store(false);
    th->join();

    return 0;
}

int Timer::restartTimer() {
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
    int i {5}; cout << "inside of ticks()" << endl;
    while (i > 0 && FLAG_FOR_TIMER.load()) {
        std::this_thread::sleep_for(time);
        std::cout << "ticks left: " << i << std::endl;
        --i;
       if(i == 0){
           cout << "ticks() -> timerStop()" << endl;
           finished = true;
           timerStop();
           cout << "after ticks() -> timerStop()" << endl;
        }
    }
   // cout <<"before timerStop in ticks() " << endl;
   // timerStop();
   // cout <<"after timerStop in ticks() " << endl;
}
