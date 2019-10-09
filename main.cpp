#include <iostream>
#include "headers/timer.h"
#include "headers/timeruser.h"
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

    Timer timer(std::chrono::duration<int> (5));
    timer.run([](){
        fun();
    });
    cout << "sleepfor" << endl;
    this_thread::sleep_for(3s);
    cout << "sleepfor" << endl;
    timer.stop();
    timer.setTimer(std::chrono::duration<int> (2));
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
