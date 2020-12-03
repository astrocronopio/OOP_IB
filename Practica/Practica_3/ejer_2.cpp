/*
Ejercicio 2 de la guia 3 de la materia de 
OPP C++ del Instituto Balseiro, Agosto 2020

Escrito por Evelyn Coronel
*/

#include <iostream>

void imprimir_fibonacci(bool flag=false, int *numero=nullptr)
{   static int fib_1;
    static int fib_2;
    static int secuencia;  
    
    if (flag) { 
        fib_1=1; fib_2=0; 
        secuencia = 0; *numero=1;
        }
    
    if (*numero==1) {
        std::cout<<"F("<<*numero<<") = "<<0;
        fib_2=0; 
        }
    
    else if (*numero==2) {
        std::cout<<"F("<<*numero<<") = "<<1; 
        fib_1=1;
        }
    
    else {
        secuencia = fib_1 + fib_2;
        std::cout<<"F("<<*numero<<") = "<<secuencia;
        fib_2=fib_1;
        fib_1=secuencia;
        }
}

int main(int argc, const char** argv) {
    
    bool flag_bool= false;
    int numero = 1;

    std::cout<< "Empezamos a imprimir números de Fibonacci.\n";
    
    while (true)
    {   
        imprimir_fibonacci(flag_bool, &numero); 
        numero++;       
        std::cout<<" Siguiente-> (0) / Reset-> (1) / Exit: Ctrl + C  ====>";
        std::cin>>flag_bool;
    }   
    return 0;
}