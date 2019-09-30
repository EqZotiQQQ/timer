#include <iostream>
#include "timer.h"
#include "timeruser.h"
using namespace std;
using namespace timer;
void fun() {
    cout << "hi!" << endl;
}
int main() {
    //TimerUser tu;
    //tu.start();
    //this_thread::sleep_for(1s);
    //tu.start();
    //this_thread::sleep_for(1s);
    //tu.stop();
    //tu.start();
    //this_thread::sleep_for(1s);

    Timer timer(2);
    timer.setTimer(5);
    timer.run([](){
        fun();
    });




   // Timer timer;
   // timer.run([](){
   //     fun();
   // });
   // cout << "HI" << endl;
   // this_thread::sleep_for(4s);
   // timer.run([](){
   //    fun();
   //    cout << "sss" << endl;
   // });
   // this_thread::sleep_for(1s);
   // timer.run([](){
   //    fun();
   //    cout << "sssAAAA" << endl;
   // });
    return 0;
}
