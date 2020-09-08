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
        int value;
    public:
        Manager();
        static int get_Instance();
        ~Manager(){};
};

//Por defecto  
Manager::Manager()
{
    std::cout<<"Se creó una variable del tipo clase Manager.";
    value=42;
}

int Manager::get_Instance()
{ 
    return value; 
}

/* ---------------------------------------- */
int main(int argc, char const *argv[])
{
    Manager prueba();
    std::cout<<Manager::get_Instance()<<"\n";
    return 0;
}
