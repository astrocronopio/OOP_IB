#ifndef ejer_10_h
#define ejer_10_h

#include <iostream>

class ejer_10
{
private:
    int valor;
public:

    ejer_10(int val) {valor = val;};
    ~ejer_10(){};

    int get_ejer_10(){return valor;};
    void set_ejer_10(int val){valor=val;};

    void print(){std::cout<<valor<<std::endl;};
};

#endif // !ejer_10_h