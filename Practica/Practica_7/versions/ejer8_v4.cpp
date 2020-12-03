/*
Ejercicio 8 de la guia 7 de la materia de 
OPP C++ del Instituto Balseiro, Septiembre 2020

Escrito por Evelyn Coronel

version 4: sigue sin funcionar
*/

#include <iostream>

class ejer8
{

private:
    int valor;
    static unsigned int N;
    static unsigned int n;


public:
    ejer8()
    {   
        n++;
        valor=n;
        std::cout<< "creando "<<valor<<"/"<<N<<", con valor"<<std::endl; 
    };        
    
    // ejer8(const ejer8& dummy):valor(dummy.valor)
    // {
    //     delete dummy;
    // };
    
    // friend void swap(ejer8_2& a1, ejer8_2& a2)
    // {
    //     using std::swap;
    //     swap(a1.valor,a2.valor);
    // }

    // ejer8 &operator=(ejer8 dummy){
    //     swap(*this, dummy);
    //     delete dummy
    //     return *this;
    // };
    
    ~ejer8()
    {   n--;
        std::cout<<"Destruyendo. Quedan "<<n<<std::endl;
    };

    int get_number_instances() const {return n;}

    void *operator new (size_t sz )
    {   
        if((n+1)>N)
            {
            std::cout<< "No pueden haber más de  "<<N<<" instancias en paralelo.\n";
            throw std::invalid_argument("");// nullptr;
            }
        else return ::new ejer8();      
    };
    
    void operator delete(void * p){ 
        ::delete p; 
    };
};

unsigned int ejer8::n=0;
unsigned int ejer8::N=4;

int main(int argc, char const *argv[])
{   
    ejer8* vector[6] ;

    for (size_t i = 0; i < 5; i++)    
    {   
        try  {
            vector[i] = new ejer8;
            }
        catch (const std::invalid_argument)  { break;}    
    } 

    delete vector[2];
    //vector[3]=nullptr;

    ejer8 * a =  new ejer8;
    //delete a;
    
    //for (size_t i = 0; i < 3; i++)
    //    delete vector[i];
      
    return 0;
}
