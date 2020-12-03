/*
Ejercicio 2 de la guia 13 de la materia de 
OPP C++ del Instituto Balseiro, Octubre 2020

Escrito por Evelyn Coronel
*/

#include <iostream>
#include <fstream>

#include <list>
#include <deque>
#include <vector>

#include <algorithm>

#include <stdlib.h>
#include <time.h>  
#include <chrono>

template< template<typename, typename=std::allocator<int>> class Container>
void sort_it(Container<int> _vector_)
{
    std::sort(_vector_.begin(), _vector_.end());
}

template<> void sort_it(std::list<int> _lista_)
{
    _lista_.sort();
}


template< template<typename, typename=std::allocator<int>> class Container>
double sort_container(Container<int> _vector_)
{   
    using namespace std::chrono;
    
    steady_clock::time_point t0 =steady_clock::now();
    sort_it(_vector_);
    steady_clock::time_point t1 =steady_clock::now();

    return (double)duration_cast<nanoseconds>(t1-t0).count();
}

std::vector<double> f(int N)
{

    std::list<int> _list_;
    std::deque<int> _deque_;
    std::vector<int> _vector_;

    int numero=0;

    float average_per_N=2;
    std::vector<double> mean_time(3);

    for (size_t k = 0; k < average_per_N; k++)
    {   
        _list_.clear();
        _deque_.clear();
        _vector_.clear();
        
        for (auto i = 0; i < N; i++)
        {
            numero = int(rand());
            _list_.push_back(numero);
            _deque_.push_back(numero);
            _vector_.push_back(numero);
        }

        mean_time[0]+=sort_container(_list_);
        mean_time[1]+=sort_container(_deque_);
        mean_time[2]+=sort_container(_vector_);

    }
    std::cout<<"\n\nCon N="<<_list_.size()<<std::endl;
    mean_time[0]=mean_time[0]/average_per_N;
    mean_time[1]=mean_time[1]/average_per_N;
    mean_time[2]=mean_time[2]/average_per_N;

    return mean_time;
}

int main(int argc, char const *argv[])
{
    srand (time(NULL));
    std::vector<double> mean_time(3);

    std::ofstream myfile ("test.dat");

    for (size_t N = 1000; N < 1000000; N+=500)
    {
        mean_time = f(N);
        // std::cout<<"\nlista: " <<mean_time[0]<<"[ns]"<<std::endl;
        // std::cout<<"_deque_: " <<mean_time[1]<<"[ns]"<<std::endl;
        // std::cout<<"_vector_: " <<mean_time[2]<<"[ns]"<<std::endl;
        myfile << N << "\t" << mean_time[0] <<"\t"<< mean_time[1] <<"\t"<<mean_time[2] <<"\n";
    }
    

    return 0;
}
