#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <atomic>



#define WAIT_FOR 1000
using namespace std;


class Timer {
private:
    chrono::milliseconds time;
    std::unique_ptr<thread> wait_thread;

private:
    std::atomic<bool> FLAG_FOR_TIMER{true};
    std::atomic<bool> RUNNING{false};
    void wait_then_call()
    {
        int i {5};

        while (i > 0 && FLAG_FOR_TIMER.load()) {
            this_thread::sleep_for(time);
            cout << "Thread " << wait_thread->get_id() << "\tcountdown at: " <<  i <<
            "\t\tFLAG_FOR_TIMER =" << FLAG_FOR_TIMER << "\tAdress =" << &FLAG_FOR_TIMER << "\tThis=" << this << std::endl;
            --i;
        }
    }

public:
    Timer() {

    }

    void timerStart() {
        FLAG_FOR_TIMER.store(true);
        this->time = chrono::milliseconds{ WAIT_FOR };
        wait_thread = make_unique<thread>(&Timer::wait_then_call, this);
    }

    void timerStop() {
       FLAG_FOR_TIMER.store(false);
       wait_thread->join();
    }

    void restartTimer() {
        timerStop();
        timerStart();

    }

    void join(){
        if (wait_thread->joinable())
            wait_thread->join();
    }

    ~Timer() {
        if (wait_thread->joinable())
            wait_thread->join();
    }


};

int main()
{
    Timer t1{};
    t1.timerStart();
    this_thread::sleep_for(std::chrono::seconds(3));
    cout << "ss" << endl;
    t1.timerStop();
    cout << "ss" << endl;
    t1.timerStart();
    this_thread::sleep_for(std::chrono::seconds(2));
    t1.restartTimer();
    this_thread::sleep_for(std::chrono::seconds(2));
   // t1.timerStart();
    return 0;
}


