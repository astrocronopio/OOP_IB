/*
Ejercicio 6 de la guia 8 de la materia de 
OPP C++ del Instituto Balseiro, Septiembre 2020

Escrito por Evelyn Coronel
*/

#include <iostream>

class ejer6
{
    public:
    int value=1;
    ejer6(){};
    ~ejer6(){};

    virtual void pepa(){
        std::cout<<"Elemento "<< std::endl;
    };
};




int main(int argc, char const *argv[])
{
    ejer6 pepe;

    //std::cout<<"e:" <<(ejer6 *)&pepe<< std::endl;
    //std::cout<<"v: "<<(void *) &pepe.value<< std::endl;
    //std::cout<<"n: "<<(void *) &pepe.name<< std::endl;
    //std::cout<<"vf: "<< (void *) &(pepe.pepa())<< std::endl;
    
    return 0;
}


