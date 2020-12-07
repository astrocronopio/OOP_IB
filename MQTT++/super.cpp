#include <iostream>


class parent
{

public:
    virtual void stuff()=0;

    void parent_fun()
    {
        stuff();
    };
};


class child :  public parent
{
public:
    void stuff();
};

    void child::stuff()
    {
        std::cout<<"Child init\n";
    }

int main(int argc, char const *argv[])
{
    child baby;

    baby.parent_fun();

    return 0;
}






