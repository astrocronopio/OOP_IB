#ifndef SPACESHIP
#define SPACESHIP 1

#include <iostream>


class SpaceShip
{
private:
    std::string name;
public:
    // SpaceShip(std::string name_init): name(name_init){
    //     std::cout<<"Creando SpaceShip ~"<< name <<"~" std::endl;};
    // ~SpaceShip(){std::cout<<"Destruyendo SpaceShip. "<< std::endl;};
    
    void fly(){std::cout<<"Estoy volando."<<std::endl;};
    
    void land2(std::string name){
        std::cout<<"(2) Aterrizé un Franchise SpaceShip:  "<<name<<std::endl;};    
};


class Shuttle : public SpaceShip{
public:
    void land(std::string name){
        std::cout<<"(1) Aterrizé un SpaceShip: "<<name<<std::endl;};
};






#endif // SpaceShip
