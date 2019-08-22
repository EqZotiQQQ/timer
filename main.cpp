#include "timer.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <string>
using namespace std;
using namespace timer;
int main()
{
    Timer t;
    cout << t.count() << endl;
    t.startTimer();
    this_thread::sleep_for(std::chrono::seconds(2));
    cout << t.count() << endl;
    t.stopTimer();
    cout << t.count() << endl;
    t.startTimer();
    this_thread::sleep_for(std::chrono::seconds(2));
    cout << t.count() << endl;
    t.stopTimer();
    cout << t.count() << endl;
    t.startTimer();
    this_thread::sleep_for(std::chrono::seconds(2));
    cout << t.count() << endl;
    t.restartTimer();
    cout << "restart" << endl;
    cout << t.count() << endl;
    this_thread::sleep_for(std::chrono::seconds(4));
    cout << t.count() << endl;
    t.stopTimer();
    cout << t.count() << endl;
    system("pause");
    return 0;
}
