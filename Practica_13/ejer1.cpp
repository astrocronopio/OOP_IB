#include <iostream>
#include <thread>
#include <vector>



void f(std::vector<int>* test)
{   std::vector<int>::iterator a;

    std::cout<<"Antes del  cambio en f"<<std::endl;

    for (auto a= test->begin(); a!=test->end(); ++a)
        std::cout<<*a<<"\t";
    
    std::cout<<std::endl;

    for (auto a= test->begin(); a!=test->end(); ++a)
        *a=3*(*a);
    
    std::cout<<"\n\nDespués del  cambio en f: "<<std::endl;
    for (auto a= test->begin(); a!=test->end(); ++a)
        std::cout<<*a<<"\t";
    
    std::cout<<std::endl;
}

void g(std::vector<int>* test)
{
    std::vector<int>::iterator a;

    std::cout<<"Antes del  cambio en g"<<std::endl;

    for (auto a= test->begin(); a!=test->end(); ++a)
        std::cout<<*a<<"\t";
    std::cout<<std::endl;

    for (auto a= test->begin(); a!=test->end(); ++a)
        *a=2*(*a);
    
    std::cout<<"\n\nDespués del  cambio en g"<<std::endl;
    for (auto a= test->begin(); a!=test->end(); ++a)
        std::cout<<*a<<"\t";

    std::cout<<std::endl;
}


int main(int argc, char const *argv[])
{   
    std::vector<int> test = {1,2,3,4,5};
    std::thread t1{f, &test};
    std::thread t2{g, &test};
    
    t1.join();
    t2.join();


    return 0;
}


