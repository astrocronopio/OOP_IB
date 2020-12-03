#include <iostream>


class ejer7
{
private:
    int value=1;
public:
    ejer7();
    ~ejer7();
};

ejer7::ejer7(/* args */)
{
}

ejer7::~ejer7()
{
}

class ejer7_child: public ejer7
{
private:
    double k=2;
public:
    ejer7_child(/* args */);
    ~ejer7_child();
};

ejer7_child::ejer7_child(/* args */)
{
}

ejer7_child::~ejer7_child()
{
}

void f(ejer7 copia )
{
    std::cout<<sizeof(copia)<< std::endl;
}

int main(int argc, char const *argv[])
{
    ejer7 pepe;
    ejer7_child pepa;

    f(pepe);
    std::cout<<sizeof(pepe)<< std::endl;
    
    f(pepa);
    std::cout<<sizeof(pepa)<< std::endl;


    return 0;
}
