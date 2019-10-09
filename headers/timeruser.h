#ifndef TIMERUSER_H
#define TIMERUSER_H
#include <mutex>
#include "timer.h"
using namespace timer;
class TimerUser
{
private:
    std::unique_ptr<Timer> timer;
public:
    void start();
    void stop();
    TimerUser();
};

#endif // TIMERUSER_H
