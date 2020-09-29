#include <iostream>

class Figura
{
public:
    //virtual void Dibujar_virtual()=0;
    virtual void Dibujar(){std::cout<<"Figura\n";};
    //void Dibujar(){std::cout<<"Figura\n";};
};


class Cuadrado:  public Figura
{
public:
    virtual void Dibujar(){std::cout<<"Cuadrado\n";};
    //void Dibujar(){std::cout<<"Cuadrado\n";};
};


class Triangulo: public Figura
{
public:
    virtual void Dibujar(){std::cout<<"Triangulo\n";};
};

int main(int argc, char const *argv[])
{   
    Cuadrado*  cuadrado= new Cuadrado;
    Triangulo* triangulo= new Triangulo;

    //Figura Harry_Styles; No puedo

    Figura * preescolar[]= {cuadrado, triangulo};

    for (size_t i = 0; i < 2; i++)
    {
        preescolar[i]->Dibujar();
    }
    

    return 0;
}
