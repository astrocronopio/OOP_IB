#include <iostream>

class Rueda
{
private:
    int value=4;
public:
    Rueda(){};
    ~Rueda(){};
};

class Motor
{
private:
    int value=1;
public:
    Motor(){};
    ~Motor(){};
};

class Auto : public Rueda, 
{
private:
    /* data */
public:
    Auto(/* args */);
    ~Auto();
};

Auto::Auto(/* args */)
{
}

Auto::~Auto()
{
}
