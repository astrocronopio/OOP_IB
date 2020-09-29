/*
Ejercicio 3 de la guia 7 de la materia de 
OPP C++ del Instituto Balseiro, Septiembre 2020

Escrito por Evelyn Coronel
*/

#include <iostream>
#include <vector>
#include "counted.h"


int main(int argc, char const *argv[])
{
    Counted primer;
    Counted segundo;
    Counted tercero;
    Counted cuarto;

    std::vector<Counted*> pepa;
    pepa.push_back(&primer);
    pepa.push_back(&segundo);
    pepa.push_back(&tercero);

    for (size_t i = 0; i < pepa.size() ; i++)
    {
        std::cout<<(counted *)
    }
    


    
    return 0;
}
