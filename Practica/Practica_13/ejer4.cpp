#include <iostream>
#include <thread>
#include <vector>

#include "synch_queue.h"

#include <chrono>

using namespace std::chrono;

using Clock = high_resolution_clock;
using TimePoint = time_point<Clock>;

milliseconds ms2 {2000};
milliseconds ms1 {1000};
auto now = system_clock::now();

const size_t Queue_size= 10;
Queue<std::string,Queue_size> synch_queue;


void capitalismo( )
{
    std::vector<std::string> palabras = {
                            "1 - Sistema económico", "2 -y social", 
                            "3 - basado en", "4 - la propiedad privada", 
                            "5 - de los medios", "6 - de producción"};  

    for (size_t i = 0; i < palabras.size(); i++)
    {   
        synch_queue.try_put_for<double, std::milli>(palabras[i], ms2);
        synch_queue.try_put_until<Clock, _V2::system_clock::duration>(palabras[i], now + milliseconds(2000));
    }

    synch_queue.print("____En la mitad de la función capitalismo___");

    for (size_t i = 0; i < palabras.size(); i++)
    {
        synch_queue.try_get_for<double, std::milli>(ms2);
        synch_queue.try_get_until<Clock, _V2::system_clock::duration>(now + milliseconds(2000));;
    }      
} 
void consumismo()
{
    std::vector<std::string> palabras = {
                    "1 - consumismo es", "2 - la compra", "3 - o acumulación de", 
                    "4 - bienes y servicios", "5 - considerados no esenciales"};

    for (size_t i = 0; i < palabras.size(); i++)
    {   
        synch_queue.try_put_for<double, std::milli>(palabras[i], ms2);
        synch_queue.try_put_until<Clock, _V2::system_clock::duration>(palabras[i], now + milliseconds(2000));
    }

    synch_queue.print("____En la mitad  de la función consumismo___");

    for (size_t i = 0; i < palabras.size(); i++)
    {
        synch_queue.try_get_for<double, std::milli>(ms2);
        synch_queue.try_get_until<Clock, _V2::system_clock::duration>(now + milliseconds(2000));;
    }
}

int main(int argc, char const *argv[])
{   

    std::thread t2{capitalismo};
    std::thread t1{consumismo};
    std::thread t3{consumismo};

    t1.join();
    t2.join();
    t3.join();

    synch_queue.print("\n\n Al final debe quedar vacío\n");
    return 0;
}
