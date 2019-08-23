#ifndef HEADER_H
#define HEADER_H

#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

enum Exit{SUCCESS_EXIT = 0, ERROR = -1};

class TimerInterface{
public:
    virtual Exit startTimer() = 0;
    virtual Exit stopTimer() = 0;
    virtual void restartTimer() = 0;
};

class Timer : public TimerInterface
{
private:
    bool running;
    chrono::steady_clock::time_point reference;
    chrono::duration<long double> accumulated;
    thread* timerThread;
    void timerLoop(){
        while(count() < 2){

        }
        stopTimer();
    }

public:
    Timer()
        :running(false),
        reference(chrono::steady_clock::now()),
        accumulated(chrono::duration<long double>(0))
    {
        timerThread = thread(timerLoop);

        cout << "thread id " << this_thread::get_id() << endl;
    }

    Exit startTimer() override final {
        cout << "thread id " << this_thread::get_id() << endl;
        if(running == false){
            running = true;
            accumulated = chrono::duration<long double>(0);
            reference = chrono::steady_clock::now();
            return SUCCESS_EXIT;
        }
        return ERROR;
    }


    Exit stopTimer() override final {
        cout << "thread id " << this_thread::get_id() << endl;
        if (running == true){
            accumulated = chrono::duration<long double> (0);
            running = false;
            return SUCCESS_EXIT;
        }
        return ERROR;
    }


    void restartTimer() override final {
        cout << "thread id " << this_thread::get_id() << endl;
        stopTimer();
        startTimer();
    }

    template <class duration_t = chrono::milliseconds>
    typename duration_t::rep count() const {
        cout << "thread id " << this_thread::get_id() << endl;
        if (running == true){
            return chrono::duration_cast<duration_t>(
                accumulated + (chrono::steady_clock::now() - reference)).count();
        } else {
            return duration_t(0).count();
        }
    }

    virtual ~Timer() {}

};


#endif // HEADER_H
