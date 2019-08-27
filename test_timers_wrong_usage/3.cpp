#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <memory>


#define WAIT_FOR 1000

using namespace std;


class Timer {
private:
    void wait_then_call()
    {
        unique_lock<mutex> lck{ mtx };
        for (int i = 5 ; i > 0; i--) {
            cout << "Thread " << wait_thread.get_id() << " countdown at: " << '\t' << i << '\n';
           // cout << "Thread " << (*wait_thread).get_id() << " countdown at: " << '\t' << i << '\n';
            cv.wait_for(lck, time );
        }
        f();
    }
    mutex mtx;
    condition_variable cv{};
    chrono::milliseconds time;
    function <void(void)> f;
    thread wait_thread;
    //unique_ptr<thread> wait_thread;

public:
    Timer() {

    }

    void timerStart(const function<void(void)>& f) {
        this->f = f;
        this->time = chrono::milliseconds{ WAIT_FOR };
        wait_thread = thread{ [this]() { wait_then_call(); } };
       // (*wait_thread) = thread{ [this]() { wait_then_call(); } };
    }

    void timerStop() {
       cout << "native handler wait_thread: " << wait_thread.native_handle() << endl;
      // std::terminate();
       cout << "ss" << endl;
      // cout << "native handler wait_thread: " << wait_thread.native_handle() << endl;
       //cout << "native handler wait_thread: " << (*wait_thread).native_handle() << endl;
    }

    void restartTimer() {

       // timerStart(f);
    }

    ~Timer() {
      wait_thread.join();
      //(*wait_thread).join();
    }


};

int main()
{
    auto f = []() {cout << "---------------- I waited to print! ----------------\n"; };
    Timer t1{};
    t1.timerStart(f);
    this_thread::sleep_for(std::chrono::seconds(2));
    t1.timerStop();

    return 0;
}
