/*
Ejercicio 6 de la guia 5 de la materia de 
OPP C++ del Instituto Balseiro, Septiembre 2020

Escrito por Evelyn Coronel
*/
 
#include <iostream> 

class ejer6_A
{
private:
    int valueA;
public:
    ejer6_A();
    ~ejer6_A();
};

class ejer6_B
{
private:
    int valueB;
public:
    ejer6_B();
    ~ejer6_B();
};
/////////////
class ejer6_C
{
private:
    int value;
    ejer6_A A;
    ejer6_B B;
public:
    ejer6_C();
    ~ejer6_C();
};

ejer6_C::ejer6_C()
{   
    value=1;
    std::cout<<"\nCreamos un objeto de la Clase Principal ejer6_C."<< std::endl;
}

ejer6_C::~ejer6_C()
{
    std::cout<<"\nDestruimos un objeto de la Clase Principal ejer6_C con value="<< value<<std::endl;
}

ejer6_B::ejer6_B()
{
    valueB=0;
    std::cout<<"\nCreamos un objeto de la Classe ejer6_B."<< std::endl;
    valueB+=1;
}

ejer6_B::~ejer6_B()
{   
    std::cout<<"\nDestruimos un objeto de la Classe ejer6_B con value="<< valueB<<std::endl;
}
    
ejer6_A::ejer6_A()
{   
    valueA=0;
    std::cout<<"\nCreamos un objeto de la Classe ejer6_A"<< std::endl;
}

ejer6_A::~ejer6_A()
{
    std::cout<<"\nDestruimos un objeto de la Classe ejer6_A con value="<< valueA <<std::endl;
}


int main(int argc, char const *argv[])
{   std::cout<<"\nSolo la clase principal: \n";
    ejer6_C prueba;

    // std::cout<<"\nSolo la clase nesteada B: \n";
    // ejer6_A::ejer6_B pruebaB;

    // std::cout<<"\nSolo la clase nesteada C: \n";
    // ejer6_A::ejer6_C pruebaC;

    return 0;
}