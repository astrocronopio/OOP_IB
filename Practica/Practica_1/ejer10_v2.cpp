/*
Ejercicio 10 de la guia 1 de la materia de 
OPP C++ del Instituto Balseiro, Agosto 2020

Escrito por Evelyn Coronel
*/

#include <iostream>
#include <string.h>

struct Complejo
{
	float x,y;
    Complejo(float x=0, float y=0)  : x(x), y(y){    }
};

typedef struct Complejo Complejo;

//print
std::ostream& operator<<(std::ostream& os, const Complejo& dummy)
{
    os << " ("<<dummy.x <<"+" <<dummy.y<<"j) ";
    return os;
}

//Sum
Complejo operator+(Complejo a, Complejo b){	 return {a.x + b.x , a.y + b.y}; }

//diff
Complejo operator-(Complejo a, Complejo b){	 return {a.x - b.x , a.y - b.y}; }

//mul
Complejo operator*(Complejo a, Complejo b)
{
	Complejo suma = {0,0};
	suma.x = a.x*b.x - a.y*b.y;
	suma.y = a.x*b.y + a.y*b.x;
	return suma;
}

//div

Complejo conjugar_complex(Complejo c)
{
	return {c.x, -c.y};
}

float modulo_cuadrado(Complejo b) 
	{Complejo dummy= b*conjugar_complex(b);
		return  dummy.x;}


Complejo operator/(Complejo a, Complejo b)
{
	Complejo Denominador = a * conjugar_complex(b);
	float a_mod = modulo_cuadrado(a);
	float b_mod = modulo_cuadrado(b);

	if (b_mod==0) {std::cout<< " No se puede dividir por cero. Voy a salir del programa\n"; exit(1);}
	else return	 Denominador = {Denominador.x/b_mod, Denominador.y/b_mod}; 
	
}


void ejercicio_10()
{
	Complejo a(2,3);
	Complejo b(3,4);
	Complejo u(1);
	Complejo c(0,1);
	Complejo e(0);

	std::cout<<"\n\n==Testeando funciones, LALA==\n\n";

	std::cout<<"Suma: "<< a << " + "<< b<< "=" << a+b << "\n";
	std::cout<<"Dife: "<< a << " - "<< b<< "=" << a-b << "\n";
	std::cout<<"Mult: "<< a << " x "<< b<< "=" << a*b << "\n";
	std::cout<<"Mult: "<< a << " x "<< e<< "=" << a*e << "\n";
	std::cout<<"Divi: "<< a << " / "<< b<< "=" << a/b << "\n";
	std::cout<<"Divi: "<< a << " / "<< u<< "=" << a/u << "\n";
	std::cout<<"Divi: "<< a << " / "<< e<< "=" << a/e << "\n";

}

int main(int argc, char const *argv[])
{
	
	ejercicio_10();
	return 0;
}
	