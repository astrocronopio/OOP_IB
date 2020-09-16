/*
Ejercicio 8 de la guia 7 de la materia de 
OPP C++ del Instituto Balseiro, Septiembre 2020

Escrito por Evelyn Coronel
*/

#include <iostream>


class Managers
{
private:
    static unsigned int n;
    static unsigned int N;
    static Managers* array;

    /////Privatizamos todo
    Managers(){};
    Managers(const Managers& dummy) = delete;
    void operator=(Managers const&) = delete;
    /////

public:
    void *operator new (size_t sz )
    {
        return ::new Managers*;
    };
    
    void *operator new[] (size_t sz )
    {
        // void **p = (void**) malloc(N);
        // for (size_t i = 0; i < N; i++)
        // {
        //     p[i] = malloc(size_Manager);
        // }
         
        // return p;
        return ::new Managers*;
    };

    void operator delete(void *p){
       // free(p);
       ::delete [] p;
       
    };
    void operator delete [](void *p){
        //free(p);
        ::delete [] p;
    };

    static Managers** get_Instance()
    {  
        if(array==0)
        {
            array = new Managers* [N];
            return array;
        }
        else return array;

    };
};

Managers** Managers::array = 0;
unsigned int Managers::n = 0;
unsigned int Managers::N = 3;

int main(int argc, char const *argv[])
{
    Managers * puntero = Managers::get_Instance();

    for (size_t i = 0; i < 3;  i++)        
    std::cout<<"Direccion "<<i+1<<"/"<<3<<": "<<(void *)puntero[i]<< std::endl;
            
    //puntero->print();
    return 0;
}
