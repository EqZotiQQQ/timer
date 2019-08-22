#ifndef TIMER_H
#define TIMER_H

#include <chrono>

namespace timer {

    using std::chrono::duration;
    using std::chrono::steady_clock;

    typedef long double ld;

    class Timer
    {
    private:
        bool started;
        bool paused;
        steady_clock::time_point reference;
        duration <ld> accumulated;

    public:
        Timer(bool start = false) :started(false), paused(false),
            reference(steady_clock::now()),
            accumulated(duration<ld>(0)) {
            if (start) {
                this->startTimer();
            }
        }

        void startTimer() {
            if (started == false) {
                started = true;
                paused = false;
                accumulated = duration<ld>(0);
                reference = steady_clock::now();
            }
            else if (paused == true) {
                reference = steady_clock::now();
                paused = false;
            }
        }

        void stopTimer() {
            if ( (started == true) && (paused == false) ) {
                accumulated = std::chrono::duration<ld>(0);
                paused = true;
            }
        }

        void restartTimer() {
            if (started == true) {
                stopTimer();
                startTimer();
            }
        }

        template <class duration_t = std::chrono::milliseconds>
        typename duration_t::rep count() const {
            if (started) {
                if (paused) {
                    return std::chrono::duration_cast<duration_t>(accumulated).count();
                }
                else {
                    return std::chrono::duration_cast<duration_t>(
                        accumulated + (steady_clock::now() - reference)).count();
                }
            }
            else {
                return duration_t(0).count();
            }
        }


        ~Timer() {}
    };
}


#endif // TIMER_H
