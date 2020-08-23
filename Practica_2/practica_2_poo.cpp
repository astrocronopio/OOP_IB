/*
Ejercicio 3 de la guia 2 de la materia de 
OPP C++ del Instituto Balseiro, Agosto 2020

Escrito por Evelyn Coronel
*/

#include <iostream>
#include <string.h>


class Stack
{
	char *v;
	int top;
	int max_size;

public:
	Stack(int size);
	~Stack();

	class Underflow{};
	class Overflow{};
	class Bad_size{};

	void  push(char c);
	char pop();
	
};

void Stack::push(char c)
{
	
}

char Stack::pop()
{

}

Stack::~Stack()
{

}


int main(int argc, char const *argv[])
{ 
	/* code */
	return 0;
}
