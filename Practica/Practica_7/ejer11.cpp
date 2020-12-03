/*
Ejercicio 13 de la guia 7 de la materia de 
OPP C++ del Instituto Balseiro, Septiembre 2020

Escrito por Evelyn Coronel
*/

#include <iostream>

class Traveler
{
private:
    std::string name;
public:
    Traveler(){};

    Traveler(std::string nm):name(nm){ std::cout<<"Creando "<<name<<std::endl;};
    ~Traveler(){};

    Traveler(const Traveler& dummy): name(dummy.name){   };
 
    friend void swap(Traveler& a1, Traveler& a2)
    {
        using std::swap;
        swap(a1.name, a2.name);
    };

    Traveler &operator=( Traveler  dummy):name(dummy.name) //move
    {  
    
       return *this;
    };

    Traveler &operator=( Traveler & dummy)// copy
    { 
        name=dummy.name;
        return *this;
    };
};


class Pager
{
private:
    std::string index;
public:
    Pager(){};

    Pager(std::string ind):index(ind){std::cout<<"Creando "<<ind<<std::endl;};
    
    ~Pager(){};

    Pager(const Pager& dummy){
        index = dummy.index;
    };
 
    friend void swap(Pager & a1, Pager& a2)
    {
        using std::swap;
        swap(a1.index, a2.index);
    };

    Pager &operator=( Pager  dummy)
    { 
        swap(*this, dummy);
        return *this;
    };

    Pager &operator=( Pager  &dummy)
    { 
        index = dummy.index;
        return *this;
    };

};

 class BussinesTraveler:  public Traveler
 {
    private:
        std::string busy;
        Pager ind;
    public:
        BussinesTraveler(){};

        BussinesTraveler(std::string nm, std::string indi):busy(nm), ind(indi) //, std::string indi) 
        {};
        
    ~BussinesTraveler(){};

    BussinesTraveler(const BussinesTraveler& dummy)
    {
        busy   = dummy.busy;
        ind    = dummy.ind;
    };
 
    friend void swap(BussinesTraveler& a1, BussinesTraveler& a2)
    {
        using std::swap;
        swap(a1.busy, a2.busy);
        swap(a1.ind, a2.ind);
    };

    BussinesTraveler &operator=( BussinesTraveler  dummy)
    { 
        swap(*this, dummy);
        return *this;
    };

    BussinesTraveler &operator=( BussinesTraveler & dummy)
    {
        busy =  dummy.busy;
        ind  =  dummy.ind;
        return *this;
    }

};


int main(int argc, char const *argv[])
{
    Traveler MarcoPolo("America"); 
    Pager Jesus("Biblia");
    BussinesTraveler JPMorgan("Pepe", "Juan");

    BussinesTraveler Santader = JPMorgan;

    return 0;
}
