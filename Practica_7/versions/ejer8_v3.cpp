/*
Ejercicio 8 de la guia 7 de la materia de 
OPP C++ del Instituto Balseiro, Septiembre 2020

Escrito por Evelyn Coronel
*/

#include <iostream>


class ejer8
{
private:
    int valor;
    static unsigned int N;
    static unsigned int n;
public:
    ejer8(){ 
         if((n+1)>N){
            std::cout<< "No pueden haber más de  "<<N<<" instancias en paralelo.\n";
            exit;
            }
         else{
             n++;
             valor=n;
             std::cout<< "creando "<<valor<<"/"<<N<<std::endl; 
         }
         };        
         
    ~ejer8(){};

    void *operator new (size_t sz )
    {   if((n+1)>N)
        {
            std::cout<< "No pueden haber más de  "<<N<<" instancias en paralelo.\n";
            exit;
        }
        
        else
        {   n++;
            return ::new ejer8();
        }    
    };
    
    // void *operator new [](size_t sz )
    // {   if((n+1)>N)
    //     {
    //         std::cout<< "No pueden haber más de  "<<N<<" instancias en paralelo.\n";
    //         exit;
    //     }
        
    //     else
    //     {   return ::new ejer8();
    //     }    
    // };

    void operator delete(void * p)
    {
        
        delete p;
    };


};



unsigned int ejer8::n=0;
unsigned int ejer8::N=4;



int main(int argc, char const *argv[])
{   
    ejer8* vector[6] ;

    for (size_t i = 0; i < 5; i++)
    {
        vector[i] = new ejer8;
    }
     
    // ejer8 a1;
    // ejer8 a2_1;
    // a2_1.~ejer8();

    // ejer8 a2_2;
    // ejer8 a4;
    // ejer8 a5;
    return 0;
}
