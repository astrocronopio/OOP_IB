/*
Ejercicio 10 de la guia 9 de la materia de 
OPP C++ del Instituto Balseiro, Agosto 2020

Escrito por Evelyn Coronel
*/

#include <iostream>
#include <vector>

template<typename T>
class minimal
{   private:
    std::vector<CTNR> contenedor;
    
    public:
    void push( CTNR dummy){
        contenedor.push_back(dummy);
    }

    void print(){
        for (auto i = 0; i < contenedor.size(); i++)
        {   std::cout<<"Contenedor << "<<i+1<<" >> \n";
            for (size_t k = 0; k < contenedor[i].size(); k++)
                std::cout<<contenedor[i][k]<<std::endl;
        }
    };
};

template<> class minimal<bool>
{

};

int main(int argc, char const *argv[])
{
    /* code */
    minimal<int, std::vector<int> > pepe;
    std::vector<int> pepa1 = {1,0,2};
    std::vector<int> pepa2 = {11,10,12};

    pepe.push(pepa1);
    pepe.push(pepa2);
    pepe.print();
    return 0;
}
