/*
Ejercicio 8 de la guia 5 de la materia de 
OPP C++ del Instituto Balseiro, Septiembre 2020

Escrito por Evelyn Coronel
*/

#include <iostream>
#include <vector> 


class Manager
{
private:
    int valor;
    static Manager* objeto;
    
    /////Privatizamos todo
    Manager(){};
    Manager(const Manager& dummy){};
    void operator=(Manager const&){};
    /////
public:
    
    static Manager* get_Instance(){
        if (objeto==nullptr) 
        {
            objeto = new Manager;
        //return dummy ;
        }
        return objeto;
    };
    
    int getManager() {return this -> valor; }
    void setManager(int dato) { this -> valor = dato; }

    void print(){std::cout<<"Direccion: "<<(void *) objeto<< std::endl;}

};


/* ---------------------------------------- */

Manager* Manager::objeto = 0; //Por alguna razón lo tengo que inicializar AFUERA o sino no la ve

int main(int argc, char const *argv[])
{   
    
    //Manager intento; NO funciona
    //Manager intento= *Manager::get_Instance(); //NO funciona
    
    /*NO  funcionan

    Manager* intento2; 
    intento2->print(); 
    intento2->setManager(4); //NO  funcionan
    std::cout<<"getter output: "<<intento2->getManager()<<"\n"; */
    
    Manager * puntero = puntero->get_Instance();
    puntero->print();
    puntero->setManager(42);
    std::cout<<"getter output: "<<puntero->getManager()<<"\n";

    std::cout<<"\nIntento crear otra instancia: \n";

    Manager * puntero2 = puntero->get_Instance();
    puntero2->print();
    std::cout<<"getter output 2: "<<puntero2->getManager()<<"\n";
    
    std::cout<<"\nPero finalmente es la misma dirección y objeto. \n";
    return 0;
}
