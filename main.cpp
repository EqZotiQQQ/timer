#include "timer.hpp"

using namespace timer;
using namespace std;
int main()
{
    Timer t1;
    t1.timerStart();
    std::this_thread::sleep_for(chrono::seconds(1));


   /* t1.restartTimer();
    std::this_thread::sleep_for(chrono::seconds(1));
    t1.timerStop();
    std::this_thread::sleep_for(chrono::seconds(1));
    t1.timerStart();*/



    std::this_thread::sleep_for(chrono::seconds(5));
    t1.timerStart();



    /*Your own test code here*/
    /*Timer t2;
    t2.timerStart();*/

    return 0;
}
