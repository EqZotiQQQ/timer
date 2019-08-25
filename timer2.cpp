#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

#define WAIT_FOR 20

using namespace std;


class Timer {
private:
    void wait_then_call()
    {
        unique_lock<mutex> lck{ mtx };
        for (int i{ 10 }; i > 0; --i) {
            cout << "Thread " << wait_thread.get_id() << " countdown at: " << '\t' << i << '\n';
            cv.wait_for(lck, time / 10);
        }
        f();
    }
    mutex mtx;
    condition_variable cv{};
    chrono::seconds time;
    function <void(void)> f;
    thread wait_thread{ [this]() {wait_then_call(); } };

public:
    Timer() {
        this->time = chrono::seconds{ WAIT_FOR };   
    }

    void timerStart(const function<void(void)>& f) {
        this->f = f;
    }

    void timerStop() {

    }

    void restartTimer() {

    }

    ~Timer() { 
        wait_thread.join(); 
    }


};

int main()
{
    auto f = []() {cout << "---------------- I waited to print! ----------------\n"; };
    Timer t1{};
    t1.timerStart(f);

    return 0;
}