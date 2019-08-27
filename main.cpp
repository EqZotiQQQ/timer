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
    t1.timerStart(boo);
    this_thread::sleep_for(10ms);
    t1.timerStop();
    this_thread::sleep_for(1s);
    t1.timerStart(too);
    return 0;
}
