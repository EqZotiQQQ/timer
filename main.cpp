
#include "header.h"
using namespace std;

int main()
{
    Timer t;
    cout << t.count() << endl;
    int status = t.startTimer();
    cout << status << " status " << endl;
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << t.count() << endl;
    t.stopTimer();
    cout << t.count() << endl;
    t.restartTimer();
    cout << t.count() << endl;
    this_thread::sleep_for(std::chrono::seconds(1));
    cout << t.count() << endl;
    t.stopTimer();
    cout << t.count() << endl;
    t.stopTimer();
    cout << t.count() << endl;
    return 0;
}
