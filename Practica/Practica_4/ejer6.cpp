/*
Ejercicio 6 de la guia 4 de la materia de 
OPP C++ del Instituto Balseiro, Septiembre 2020

Escrito por Evelyn Coronel
*/
#include "stack.h"  
#include <iostream>
#include <vector> 



void Stack::push(std::string* c)
{
	if (top == max_size) throw Overflow{};
	v[top++] = c;
	std::cout << "Pushing \'" << *c << "\'. ";
	std::cout << "Quedan " << max_size - top <<" de "<<max_size << " lugares disponibles.\n";
}

std::string Stack::pop()
{
	if( top == 0) throw Underflow{};
	top--;
	std::cout << "Poping \'" << *(v[top]) <<"\'\n";
	return *(v[top]);
}


int main(int argc, char const *argv[])
{ 
    std:: vector <std::string*> str_vector;
    std::string s[6]={"Esto", "es", "una", "prueba", "sobre vector of pointers a objetos", "sobre Stack"};
    
    str_vector.push_back(&s[0]);
    str_vector.push_back(&s[1]);
    str_vector.push_back(&s[2]);
    str_vector.push_back(&s[3]);
    str_vector.push_back(&s[4]);

    Stack pepe(str_vector.size(), str_vector);
    std::cout<<pepe;

    pepe.pop();

    pepe.push(&s[5]);
    std::cout<<pepe;


    return 0;
} 
