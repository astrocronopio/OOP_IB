#include <iostream>
#include <chrono>
using namespace std::chrono;
milliseconds null {0};
milliseconds ms1_2 {100};

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
    void stuff()
    {
        std::cout<<"Child init\n";
    }
};

int main(int argc, char const *argv[])
{
    auto now = system_clock::now();

    while ( (system_clock::now() - now ) < ms1_2 )
            std::cout<<"Print bitch\n";
    return 0;
}






