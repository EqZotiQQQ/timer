#include "../headers/timeruser.h"
#include <iostream>
#include <mutex>

using namespace std;
TimerUser::TimerUser()
{
    timer = unique_ptr<Timer>(new Timer);
}
void TimerUser::start(){
    timer->run([](){
        cout << "hi!" << endl;
        cout << this_thread::get_id() << endl;
    });

}
void TimerUser::stop(){
    cout << "Stop!" << endl;
    timer->stop();
}

