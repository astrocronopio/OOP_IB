#include <iostream>
#include <thread>

#include "synch_queue.h"

#include <chrono>

using namespace std::chrono;

using Clock = high_resolution_clock;
using TimePoint = time_point<Clock>;

int main(int argc, char const *argv[])
{   
    milliseconds ms2 {2000};
    milliseconds ms1 {1000};

    auto now = system_clock::now();

    Queue<std::string,2> synch_queue;
    
    synch_queue.try_put_for<double, std::milli>("pepe", ms2);
    synch_queue.try_put_until<Clock, _V2::system_clock::duration>("juan", now + milliseconds(2000));
    
    synch_queue.try_put("error tail=max");

    synch_queue.try_get();
    synch_queue.try_get();
    synch_queue.try_get(); // Error tail=0

    return 0;
}
