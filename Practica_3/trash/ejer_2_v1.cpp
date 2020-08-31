/*
Ejercicio 2 de la guia 3 de la materia de 
OPP C++ del Instituto Balseiro, Agosto 2020

Escrito por Evelyn Coronel
*/

#include <iostream>

int  Fibonacci ( int numero)
{
    return numero>1? Fibonacci(numero-1) + numero : 1;
}

static int numero=0;
static int secuencia=0;
static int init_num=0;

void imprimir_fibonacci(bool flag=false)
{   
    if (flag) {
         numero=init_num;
         secuencia= Fibonacci(numero);
                };
    
    std::cout<<"F("<<numero<<") = "<<secuencia;
    numero+=1;
    secuencia+=numero;
}

int main(int argc, const char** argv) {
    
    bool flag  = true;
    bool flag_bool= false;
    std::cout<< "Empezamos a imprimir números de Fibonacci.\n";
    std::cout<< "¿Con qué posición empezamos? \n";
    std::cin>>init_num;
    numero = init_num;
    
    while (flag == true)
    {   
        imprimir_fibonacci(flag_bool);
        std::cout<<"¿Imprimimos el siguiente? si(1)/ no(0)  \n "; 
        std::cin>>flag;
        if (flag==false) break;
        std::cout<<"¿Reseteamos al primer número que ingresamos? si(1)/no(0) ";
        std::cin>>flag_bool;
    }
    
    return 0;
}