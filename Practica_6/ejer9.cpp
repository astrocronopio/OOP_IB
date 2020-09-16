/*
Ejercicio 9 de la guia 6 de la materia de 
OPP C++ del Instituto Balseiro, Septiembre 2020

Escrito por Evelyn Coronel
*/


#include <iostream> 


class Orange
{
private:
   int naranjita;
public:
    Orange(){naranjita=42;};
    ~Orange(){};
    int getter_orange() const {return naranjita;}
};



class Apple
{
private:
    int manzanita;
public:
    Apple(Orange Naranja){manzanita = 2.0*Naranja.getter_orange();};
    int getter_apple() const {return manzanita;}
    ~Apple(){};
};


int f(Apple Manzana){
    return Manzana.getter_apple();

}

int main(int argc, char const *argv[])
{
    Orange Naranja;
    Apple Manzana(Naranja);
   
    std::cout<<"Output f(Naranja): "<<f(Naranja)<<std::endl; //QUEEEEEEE??????????? 
    std::cout<< "Naranja.getter_orange output: "<<Naranja.getter_orange()<<"\n";
    std::cout<<std::endl;
    std::cout<<"Output f(Manzana): "<<f(Manzana)<<std::endl;
    std::cout<< "Manzana.getter_apple output: "<<Manzana.getter_apple()<<"\n";;
    return 0;
}
