/*
Ejercicio 5 de la guia 4 de la materia de 
OPP C++ del Instituto Balseiro, Agosto 2020

Escrito por Evelyn Coronel
*/
#include <iostream>

class Message
{
private:
    std::string text;
public:
    Message(std::string initstate);
    ~Message(){};
    void print(){std::cout<<text<<"\n";};
    void print2(std::string otro = ""){std::cout<<text+otro<<"\n";}
};

Message::Message(std::string init_message){ text=init_message; }

void print(Message test, std::string otro)
{
    test.print();
    std::cout<<otro<<"\n";
}


int main(int argc, char const *argv[])
{   
    Message pepe("hola");
    std::cout<<"-- Función Message::print() -- \n";
    pepe.print();
    std::cout<<"\n-- Función print() --\n";
    print(pepe, "mundo");

    /* Creo que es más práctica está función, en vez de print */
    std::cout<<"\n-- Función Message::print2(otro) --\n";
    pepe.print2(" mundo");

    return 0;
}
