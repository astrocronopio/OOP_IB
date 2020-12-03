/*
Ejercicio 9 de la guia 10 de la materia de 
OPP C++ del Instituto Balseiro, Agosto 2020

Escrito por Evelyn Coronel
*/

#include <iostream>

void test()
{
    try
    {
        throw std::length_error("Try anidado");
        throw std::runtime_error("Err Condition");
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        test();    
    }
    catch(const std::length_error & e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
