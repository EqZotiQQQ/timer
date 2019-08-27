#include "timer.hpp"
#include <iostream>
using namespace timer;
using namespace std;
void foo(){
    cout << "111" << endl;
}
void boo(){
    cout << "211" << endl;
}
void too(){
    cout << "311" << endl;
}
int main()
{
    Timer t1;

    t1.timerStart(foo);
    this_thread::sleep_for(3s);
    t1.timerStart(too);
    this_thread::sleep_for(1s);
    t1.timerStop();
    this_thread::sleep_for(1s);
    t1.timerStart(too);
    this_thread::sleep_for(1s);
    t1.timerRestart(too);
    t1.timerStop();
    t1.timerStop();
    t1.timerRestart(too);

   


    return 0;
}
