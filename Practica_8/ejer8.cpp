#include <iostream>


class ejer8
{
public:
    int value=1;

    void setter(int valor){value=valor; }

    virtual ejer8 * clone() 
    { 
        ejer8* dummy = new ejer8; 
        dummy->setter(this->value);
        std::cout<<"Clone Padre\n";
        return dummy;
    };
};


class ejer8_child_1: public ejer8
{ public:

    virtual ejer8_child_1* clone()
     {   ejer8_child_1* dummy = new ejer8_child_1();
         dummy->setter(this->value);  
         std::cout<<"Clone Child 1\n";
         return dummy;
     };
};

class ejer8_child_2: public ejer8
{   //std::cout<<typeid(dynamic_cast<ejer8_child_1*>(pepa1_upcast->clone())).name()<<std::endl;
    public:
    virtual ejer8_child_2* clone()
     {   ejer8_child_2* dummy = new ejer8_child_2();
         std::cout<<"Clone Child 2\n";
         dummy->setter(this->value);  
         return dummy;
     };
};

int main(int argc, char const *argv[])
{
    ejer8 pepe;
    pepe.setter(24);

    ejer8_child_1 pepa_child_1;
    pepa_child_1.setter(1);
    
    ejer8_child_2 pepa_child_2;
    pepa_child_2.setter(2);

    ejer8 * pepa1_upcast = &pepa_child_1; 
    ejer8 * pepa2_upcast = &pepa_child_2; 

    ejer8* pepe_clone = pepe.clone();

    std::cout<<"\nBase clone()\n";

    std::cout<<typeid(*pepe_clone).name()<<std::endl;

    std::cout<<"\nChild 1 clone()\n";
    std::cout<<"Original: (original) "  <<typeid(pepa_child_1.clone()).name()<<std::endl;
    std::cout<<"Original: (con upcast) "<<typeid(pepa1_upcast->clone()).name()<<std::endl;
    //Si lo intento ponerselo a un puntero child, upcast->clone() me tira error
    //A menos que haga un downcast
    std::cout<<"Original: (con downcast) "<<typeid(dynamic_cast<ejer8_child_1*>(pepa1_upcast->clone())).name()<<std::endl;

    std::cout<<"\nChild 2 clone()\n";
    std::cout<<"Original: (original) "  <<typeid(pepa_child_2.clone()).name()<<std::endl;
    std::cout<<"Original: (con upcast) "<<typeid(pepa2_upcast->clone()).name()<<std::endl;
    std::cout<<"Original: (con downcast) "<<typeid(dynamic_cast<ejer8_child_2*>(pepa2_upcast->clone())).name()<<std::endl;

    return 0;
}
