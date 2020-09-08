/*
Ejercicio 6 de la guia 5 de la materia de 
OPP C++ del Instituto Balseiro, Septiembre 2020

Escrito por Evelyn Coronel
*/
 
#include <iostream>
#include <vector> 

class ejer6_A
{
private:
    int value;
public:
    ejer6_A();
    ~ejer6_A();
    //void set_A()       {value+=1;};
    //int  get_A const (){return value;};

    class ejer6_B
    {
    private:
        int valueB;
    public:
        ejer6_B();
        ~ejer6_B();
    };

    class ejer6_C
    {
    private:
        int valueC;
    public:
        ejer6_C();
        ~ejer6_C();
    };

};

ejer6_A::ejer6_A()
{   value=0;
    std::cout<<"Creamos un objeto de la Classe ejer6_A."<< std::endl;
    value+=1;
}

ejer6_A::~ejer6_A()
{
    std::cout<<"\nDestruimos un objeto de la Classe ejer6_A con value="<< value<<std::endl;
}

    ejer6_A::ejer6_B::ejer6_B()
    {
        valueB=0;
        std::cout<<"\nCreamos un objeto de la Classe ejer6_B."<< std::endl;
        valueB+=1;
    }
    
    ejer6_A::ejer6_B::~ejer6_B()
    {std::cout<<"\nDestruimos un objeto de la Classe ejer6_B con value="<< valueB<<std::endl;
    }

        
    ejer6_A::ejer6_C::ejer6_C()
    {   
        valueC=0;
        std::cout<<"\nCreamos un objeto de la Classe ejer6_C.\n";
        valueC+=1;
    }
    
    ejer6_A::ejer6_C::~ejer6_C()
    {
        std::cout<<"\nDestruimos un objeto de la Classe ejer6_C con value="<< valueC <<std::endl;
    }

int main(int argc, char const *argv[])
{   std::cout<<"\nSolo la clase principal: \n";
    ejer6_A prueba;

    std::cout<<"\nSolo la clase nesteada B: \n";
    ejer6_A::ejer6_B pruebaB;

    std::cout<<"\nSolo la clase nesteada C: \n";
    ejer6_A::ejer6_C pruebaC;

    return 0;
}
