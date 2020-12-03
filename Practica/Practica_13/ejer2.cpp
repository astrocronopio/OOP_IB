#include <iostream>
#include <thread>
#include <vector>

#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable mcond;

void f(std::vector<int>* test)
{   std::vector<int>::iterator a;
    std::unique_lock<std::mutex> lck{m};

    std::cout<<"\n\nAntes del  cambio en f"<<std::endl;

    for (auto a= test->begin(); a!=test->end(); ++a)
        std::cout<<*a<<"\t";
    
    std::cout<<std::endl;

    for (auto a= test->begin(); a!=test->end(); ++a)
        *a=3*(*a);
    
    std::cout<<"Después del  cambio en f: "<<std::endl;
    for (auto a= test->begin(); a!=test->end(); ++a)
        std::cout<<*a<<"\t";
    
    std::cout<<std::endl;
    mcond.notify_one();
}

void g(std::vector<int>* test)
{   
    std::unique_lock<std::mutex> lck{m};
    mcond.wait(lck); 
    // Si mando primero g a correr, y pongo esta línea, 
    // fuerza a que el otro thread corra y termine 
    // hasta llegar al notify_one(), donde empieza el thread
    // de g a correr

    std::vector<int>::iterator a;

    std::cout<<"\n\nAntes del  cambio en g"<<std::endl;

    for (auto a= test->begin(); a!=test->end(); ++a)
        std::cout<<*a<<"\t";
    std::cout<<std::endl;

    for (auto a= test->begin(); a!=test->end(); ++a)
        *a=2*(*a);
    
    std::cout<<"Después del  cambio en g"<<std::endl;
    for (auto a= test->begin(); a!=test->end(); ++a)
        std::cout<<*a<<"\t";

    std::cout<<std::endl;
}


int main(int argc, char const *argv[])
{   
    std::vector<int> test = {1,2,3,4,5};
    
    std::thread t1{g, &test}; 
    std::thread t2{f, &test};

    //al reves, nunca se ejecuta notify_one()
    // std::thread t3{g, &test};
    
    t1.join();
    t2.join();
    //t3.join();


    return 0;
}
