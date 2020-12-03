#include "ejer_10.h"

extern ejer_10 test;

int main(int argc, char const *argv[])
{
    std::cout<<"Con init(): ";test.print();
    test.set_ejer_10(54);
    std::cout<<"Con print(): "; test.print();
    std::cout<<"Con getter : "<< test.get_ejer_10()<<"\n";
    return 0;

}
 