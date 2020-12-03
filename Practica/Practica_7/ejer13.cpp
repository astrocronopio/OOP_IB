#include <iostream>
#include <vector>


class cosa
{
private:
    int value = 1;
public:
    cosa(){std::cout<<"Hola "<< value <<std::endl; value++;};
    ~cosa(){std::cout<<"Chau "<< value <<std::endl; value--;};
};

int main(int argc, char const *argv[])
{
    std::vector<cosa> pepe;

    cosa juan;
    pepe.push_back(juan);

    cosa* jose= &juan;
    std::vector<cosa *> pepa;
    pepa.push_back(jose);
    
    return 0;
}
