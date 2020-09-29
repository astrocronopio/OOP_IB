#include <iostream>
#include <cassert> //Para el assert
#include "ejer8.h"


int main()
{   ejer8::heapInitializer();
    
    // Arreglo de punteros a ejer8
    int test=5;
    ejer8 *prueba[test]; // pero solo tengo 4

    //ejer8 xinstance; //! Error porque ~ejer8 es privado
    int k=0;
    try {
        for( k = 0; k < test; ++k ) 
            prueba[k] = new ejer8;

    } catch( const std::exception &e ) {
        std::cout<<"Te pasate de instancias! "<<  e.what() << std::endl;
    }

    std::cout << "\nAllocamos: " << k  <<" instancias"<< std::endl;

    ejer8::destroy(prueba[3]);  //Pruebo en destruir
    ejer8* pepe = new ejer8;    //Pruebo en instanciar

    return 0;
}