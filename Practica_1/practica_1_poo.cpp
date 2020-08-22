/*
Ejercicio 10 de la guia 1 de la materia de 
OPP C++ del Instituto Balseiro, Agosto 2020

Escrito por Evelyn Coronel
*/

#include <iostream>
#include <string.h>

typedef struct Complejo
{
	float x,y;
} Complejo;



//print

void print_complex(Complejo dummy)
{
	std::cout<< " ("<<dummy.x <<"+" <<dummy.y<<"j) ";
}

//ingresar
Complejo init_complex(float x=0, float y = 0)
{	
	Complejo dummy = {.x=x, .y=y};
	if (y==0 && x!=0) std::cout<<"Se inicializó un número real: "<<x<<std::endl;
	else if (x==0 && y!=0)  std::cout<<"Se inicializó un número imaginario: "<<y<< "j"<<std::endl;
	else if (x==0 && y==0)  std::cout<<"Se inicializó el complejo nulo 0+0j "<<std::endl;
	else {
		std::cout<< "El número complejo es "; 
		print_complex(dummy); 
		std::cout<< "\n";}
	return dummy;
}


//sum

Complejo sum_complex(Complejo a, Complejo b)
{	
	return {a.x + b.x , a.y + b.y};
}
//diff

Complejo dif_complex(Complejo a, Complejo b)
{
	return {a.x - b.x , a.y - b.y};
}
//mul

Complejo mul_complex(Complejo a, Complejo b)
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
	{return mul_complex(b,conjugar_complex(b)).x;}

Complejo div_complex(Complejo a, Complejo b)
{
	Complejo Denominador = mul_complex(a, conjugar_complex(b));
	float a_mod = modulo_cuadrado(a);
	float b_mod = modulo_cuadrado(b);

	if (b_mod==0) {std::cout<< " No se puede dividir por cero. Voy a salir del programa\n"; exit(1);}
	else return	 Denominador = {Denominador.x/b_mod, Denominador.y/b_mod}; 
	
}

void testing_function(Complejo (*f) (Complejo,Complejo),
						 Complejo a, Complejo b, const char* nombre, const  char* simbolo)
{	std::cout<<nombre;
	print_complex(a); 
	std::cout<<simbolo;
	print_complex(b);
	std::cout<<"=";
	print_complex(f(a,b));
	std::cout<<"\n";
}

void ejercicio_10()
{
	Complejo a= init_complex(2,3);
	Complejo b= init_complex(3,4);
	Complejo u= init_complex(1);
	Complejo c= init_complex(0,1);
	Complejo e= init_complex();

	std::cout<<"\n\n==Testeando funciones==\n\n";

	testing_function(sum_complex, a, b, "suma: ","+");
	testing_function(dif_complex, a, b, "resta: ","-");
	testing_function(mul_complex, a, b, "multi: ","x");
	testing_function(mul_complex, a, e, "multi: ","x");
	testing_function(div_complex, a, b, "divid: ","/");
	testing_function(div_complex, a, u, "divid: ","/");
	testing_function(div_complex, a, e, "divid: ","/");

}

int main(int argc, char const *argv[])
{
	
	ejercicio_10();
	return 0;
}
	