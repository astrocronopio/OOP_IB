#ifndef COUNTED_H
#define COUNTED_H 1

#include <iostream>

class Counted
{
private:
    int id;
    static int count;
public:
    Counted():id(count++){
        std::cout<<"Creando Variable id: "<< id<< std::endl;
        };
    
    ~Counted(){
        std::cout<<"Destruyendo Variable id: "<<id<< std::endl;
        };
};

int Counted::count = 0.0;

#endif // COUNTED_H