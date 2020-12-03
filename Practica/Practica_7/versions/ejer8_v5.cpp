/*
Ejercicio 8 de la guia 7 de la materia de 
OPP C++ del Instituto Balseiro, Septiembre 2020

Escrito por Evelyn Coronel

version 4: sigue sin funcionar
*/

#include <iostream>

class Framis 
{
private:

    enum { sz = 10 };
    char c[sz]; // To take up space, not used
    static unsigned char pool[];
    static bool alloc_map[];
    
public:
    enum { psize = 100 }; // frami allowed
    Framis() { std::cout << "Framis()\n"; }
    ~Framis(){ std::cout << "~Framis() ... "; }
    void *operator new(size_t);
    void operator delete(void*);
};

unsigned char Framis::pool[psize * sizeof(Framis)];
bool Framis::alloc_map[psize] = {false};



void Framis::operator delete(void*m) 
{   if (!m) return; 

    uintptr_t block = (uintptr_t) m -  (uintptr_t)pool;
    block /= sizeof(Framis);   

    std::cout << "freeing block " << block << std::endl;    // Mark it free:
    
    alloc_map[block] = false;
}


void* Framis::operator new(size_t) 
{
    for (int i = 0; i < psize; i++)
        if (!alloc_map[i]) 
        {
            std::cout << "using block " << i << std::endl;
            alloc_map[i] = true; // Mark it used
            
            return pool + (i * sizeof(Framis));
            }    
        
        std::cout << "out of memory" << std::endl;
        throw std::bad_alloc();
        }


int main(){    
    Framis *f[Framis::psize];

    try
    { 
        for (int i = 0; i < Framis::psize; i++) 
            f[i] = new Framis;
        new Framis; // Out of memory    
    } 
    catch (std::bad_alloc) {
        std::cerr << "Out of memory!" << std::endl;    
        }
    
    delete f[10];
    f[10] = nullptr;    // Use released memory:    
    Framis *x = new Framis;
    
    delete x;
    
    for (int j = 0; j < Framis::psize; j++)
        delete f[j]; // Delete f[10] OK

    return 0;
}
