/*
Ejercicio 8 de la guia 6 de la materia de 
OPP C++ del Instituto Balseiro, Septiembre 2020

Escrito por Evelyn Coronel
*/


#include <iostream> 

class ejer8_1
{
private:
    unsigned int sz;
    float * array;

public:
    // 1 Construct
    ejer8_1(unsigned int size=1)
    : sz(size), array(new float(sz)) {};
    
    // 2 Copy Construct
    ejer8_1(const ejer8_1& dummy)
    : sz(dummy.sz), array(new float(sz))
    {
        std::copy(dummy.array, dummy.array + sz, array);
    }

    void print() const {std::cout<<"Direccion: "<<(void *) array<< std::endl;};

    // 3  Destruct
    ~ejer8_1(){delete [] array;};
};


class ejer8_2
{
private:
    unsigned int sz;
    float * array;

public:
    // 1 Construct
    ejer8_2(unsigned int size=1)
    : sz(size), array(new float(sz)) {};
    
    // 2 Copy Construct
    ejer8_2(const ejer8_2& dummy)
    : sz(dummy.sz), array(new float(sz))
    {
        std::copy(dummy.array, dummy.array + sz, array);
    }

    void print(){std::cout<<"Direccion: "<<(void *) array<< std::endl;}
    
    friend void swap(ejer8_2& a1, ejer8_2& a2)
    {
        using std::swap;
        swap(a1.array,a2.array);
    }

    ejer8_2 &operator=( ejer8_2  dummy)
    {   
        // /ejer8_2 tmp;
        swap(*this, dummy);
        //if (&dummy != this) {
        //    *array = *dummy.array;}
        return *this;
    }

    // 3  Destruct
    ~ejer8_2(){delete [] array;};
};

int main(int argc, char const *argv[])
{
    ejer8_1 a(3);
    a.print();
    ejer8_1 b=a;
    b.print();
    //
    std::cout<<"\nEn la otra clase\n"; 
    //
    ejer8_2 b_1;
    b_1.print();
    ejer8_2 b_2=b_1;
    b_2.print();

    return 0;
}

