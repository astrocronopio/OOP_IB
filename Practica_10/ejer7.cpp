/*
Ejercicio 7 de la guia 10 de la materia de 
OPP C++ del Instituto Balseiro, Agosto 2020

Escrito por Evelyn Coronel
*/


#include <iostream>

class error_1 : public std::runtime_error
{ 
    public:
    error_1(std::string msg=""): std::runtime_error(msg){};

    virtual const char* what() const throw()
    {
        return "Error 1";
    }
};


class error_2 : public std::runtime_error
{ 
    public:
    error_2(std::string msg=""):std::runtime_error(msg){};

    virtual const char* what() const throw()
    {
        return "Error 2";
    }
};


int main(int argc, char const *argv[])
{   //Catching con clase heredada
    try
    {
        throw error_1();
    }
    catch(error_1 & e)
    {
        std::cout << e.what() << '\n';
    }


    //Catching con Run-time error
    try
    {
        throw error_2();
    }
    catch(const std::runtime_error& e)
    {   
        std::cout << "Run-time error " << '\n';
    }
    
    return 0;
}
