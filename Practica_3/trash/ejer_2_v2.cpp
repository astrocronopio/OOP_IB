/*
Ejercicio 2 de la guia 3 de la materia de 
OPP C++ del Instituto Balseiro, Agosto 2020

Escrito por Evelyn Coronel
*/

#include <iostream>




int  Fibonacci ( int numero)
{   if (numero==1) return 0;
    if (numero==2) return 1; 
    else return Fibonacci(numero-1) + Fibonacci(numero-2);
}


static int fib_1=1;

static int fib_2=0;
static int init_num=0;
static int secuencia=0;

void imprimir_fibonacci(bool flag=false, int *numero=0)
{  
    if (flag) { fib_1=0; fib_2=1; secuencia = fib_1 + fib_2; *numero=1;}
    std::cout<<"F("<<*numero<<") = "<<secuencia;
    *numero+=1;
}

int main(int argc, const char** argv) {
    
   // bool flag  = true;
    bool flag_bool= false;
    std::cout<< "Empezamos a imprimir números de Fibonacci.\n";
    //std::cout<< "¿Con qué posición empezamos?\n"; std::cin>>init_num;
    int numero = 1;
    

    
    while (true)
    {   secuencia = fib_1 + fib_2;
        //secuencia = secuencia + fib_2;
        imprimir_fibonacci(!flag_bool, &numero);
        fib_2=fib_1;
        fib_1=secuencia;
        //fib_2= secuencia;
        
        std::cout<<" Siguiente: (1)  ----  Reset:  (0) --- Exit: Ctrl + C ";
        std::cin>>flag_bool;

    }
    
    return 0;
}