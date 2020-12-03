/*
Ejercicio 8 de la guia 4 de la materia de 
OPP C++ del Instituto Balseiro, Septiembre 2020

Escrito por Evelyn Coronel
*/

#include <iostream>
#include <vector> 


class Manager
{

private:
    int valor;
    Manager();

public:
    static Manager* get_Instance();
};


Manager* Manager::get_Instance()
{
    Manager* dummy ;
    //dummy->valor=2;
    //std::cout<<dummy->valor;
    return dummy ;//dummy;
}

/* ---------------------------------------- */

int main(int argc, char const *argv[])
{   
    //Manager intento; NO funciona
    Manager* intento2;
    Manager * puntero = Manager::get_Instance();
    
    return 0;
}
