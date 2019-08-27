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

void test1() {
    Timer t1(boo);
    t1.start(5s);
    t1.stop();
}

int main()
{
    cout << "Start test1" << endl;
    test1();
    cout << "Finish" << endl;

    Timer t1(foo);

    cout << "t1.start(2s);" << endl;
    t1.start(2s);
    this_thread::sleep_for(3s);
    cout << "t1.start(5s);" << endl;
    t1.start(5s);
    this_thread::sleep_for(10ms);
    cout << "t1.stop();" << endl;
    t1.stop();
    this_thread::sleep_for(1s);

    cout << "t1.start(3s);" << endl;
    t1.start(3s);

    return 0;
}
