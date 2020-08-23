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
	const char *name;
	int top, max_size;

public:
	Stack(int size, const char* name);
	~Stack();

	class Underflow{ };
	class Overflow{ };
	class Bad_size{ };

	void  push(char c);
	char pop();

	friend std::ostream &operator<<(std::ostream &os, const Stack &stack_dummy)
	{	if (stack_dummy.top==0) os<<"\nEl stack  \""<<stack_dummy.name<<"\" está vacío.\n\n";
		else {
			os<<  "\nImprimiendo el stack \""<<stack_dummy.name << "\":\n__Stack__\n\n";
			for (int i = stack_dummy.top-1; i >= 0 ; i--)
				os<<"Orden "<< i+1 <<"/"<<stack_dummy.max_size<<":"<< stack_dummy.v[i]<< "\n";
			os<<"_________\n\n";}
		return os;	
	}
};

void Stack::push(char c)
{
	if (top == max_size) throw Overflow{};
	v[top++] = c;
	std::cout << "Pushing \'" << c << "\' a \""<< name <<"\". ";
	std::cout << " Quedan " << max_size - top <<" de "<<max_size << " lugares.\n";
}

char Stack::pop()
{
	if( top == 0) throw Underflow{};
	top--;
	std::cout << "Poping \'" << v[top] <<"\' de \""<< name <<"\" \n";
	return v[top];
}

Stack::~Stack() {delete [] v;}

Stack::Stack(int s, const char* name_init){
	top=0;
	if (s<=0 || s>1000) throw Stack::Bad_size{};
	max_size = s;
	name = name_init;
	std::cout<<"Se creó el stack \""<<name<<"\" con lugar para "<<max_size<<" elementos.\n";

	v= new char[s];
}

int main(int argc, char const *argv[])
{
	Stack s_var2(10, "primer stack");

	s_var2.push('1');
	s_var2.push('2');
	s_var2.push('3');

	std::cout<<s_var2;

	s_var2.pop()  ;
	s_var2.pop()  ;

	std::cout<<s_var2;


	Stack s_var1(2, "segundo stack");
	std::cout << s_var1;
	s_var1.push('1');
	s_var1.push('2');

	s_var1.push('F');

	//Stack s_var3(2, "tercer stack");

	return 0;
}
