/*
Ejercicio 12 de la guia 7 de la materia de 
OPP C++ del Instituto Balseiro, Septiembre 2020

Escrito por Evelyn Coronel
*/

#include <iostream>
#include <string>
#include "spaceship.h"

int main(int argc, char const *argv[])
{   
    Shuttle sputnik;
    sputnik.land("Sputnik");

    ////////////////////////////////////////////
    /*
    No funciona porque el método land() está en la 
    clase hijo, y no en la clase base. Si el método 
    land estuviera en la clase base no hay problema
    */

    //SpaceShip *Challenger = &sputnik;
    //Challenger->land("Challenger");

    ////////////////////////////////////////////
    /*
    Ahora puse un metodo land2() en la clase base
    y funciona
    */

    Shuttle Enterprise;
    Enterprise.land2("Enterprise");

    SpaceShip *Millenium_Falcon = &Enterprise;
    Millenium_Falcon->land2("Millenium Falcon");

    return 0;
}
