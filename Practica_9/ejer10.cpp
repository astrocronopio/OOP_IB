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
    T* contenedor;
    int N; //Cuantos elementos tiene
    int max;
    
    public:

    minimal(int n): contenedor(new T[n]), N(0), max(n){};

    T* operator*(){return contenedor;};

    T& operator[](int ind) const{
        if (ind > N)
        {
            std::cout<<"Out of bounds!\n";
            exit(0);
        }
        return *(contenedor + ind);
    };


    void push( T dummy)
    {   
        if (N==max){
            std::cout<<"Maxima capacidad alcanzada\n";
            return;
        }
        std::cout<<"Pushing: "<<dummy<<std::endl ;
        (*this)[N] = dummy;
        N=N+1;
    };

    int size() const { return N;  };


    friend std::ostream& operator<<(std::ostream& os, const minimal <T > &conte)
    {
        for (auto i = 0; i < conte.size(); i++)
        {   os<<"Elemento << "<<i+1<<" >>: ";
                os<<conte[i]<<std::endl;
        }
        return os;
    };

    ~minimal(){delete [] contenedor;};
};


int bool_to_char(int n)
{
    if (n%sizeof(char)==0)
        return int(n/sizeof(char));

    return  int(n/sizeof(char)) + 1;
}


template<> class minimal<bool>
{
private:
    char* contenedor;
    int N; //Cuantos elementos tiene
    int max;
    
    public:

    minimal(int n): contenedor(new char[bool_to_char(n)]), N(0), max(n){};

    char* operator*(){return contenedor;};

    bool operator[](int ind) const{
        if (ind > N)
        {
            std::cout<<"Out of bounds!\n";
            exit(0);
        }
        else
        {   return contenedor[bool_to_char(ind)]>>(ind%sizeof(char)) ;
            //return out;
            // out= out%2;
            // if (out==1) return true;
            // else return false;
        }
    };


    void push( bool dummy)
    {   
        if (N==max){
            std::cout<<"Maxima capacidad alcanzada\n";
            return;
        }
        else
        {   std::cout << std::boolalpha;
            std::cout<<"Pushing: "<<dummy<<std::endl ;
            contenedor[bool_to_char(N)] += dummy;
            N=N+1;
            std::cout<< std::noboolalpha;
        }
    };

    int size() const { return N;  };


    friend std::ostream& operator<<(std::ostream& os, const minimal<bool> &conte)
    {   os << std::boolalpha;
        for (auto i = 0; i < conte.size(); i++)
        {   os<<"Elemento << "<<i+1<<" >>: ";
                os<<conte[i]<<std::endl;
        }
        os << std::noboolalpha;
        return os;
    };

    ~minimal(){delete [] contenedor;};


};

int main(int argc, char const *argv[])
{
    /* code */
    minimal<int > pepe(2);
    int pepa1=1;
    int pepa2=2;
    int pepa3=3;

    pepe.push(pepa1);
    pepe.push(pepa2);
    pepe.push(pepa3);

    std::cout<< pepe<<std::endl;

std::cout<<std::endl;

    minimal<char> main_vector(10);
    int c1='a';
    int c2='b';
    main_vector.push(c1);
    main_vector.push(c2);
    std::cout<< main_vector <<std::endl;

std::cout<<std::endl;

    minimal<bool> bool_vector(5);

    bool_vector.push(true);
    bool_vector.push(true);
    bool_vector.push(false);
    bool_vector.push(true);
    bool_vector.push(false);
    bool_vector.push(false); // max cap

    std::cout<< bool_vector <<std::endl;

    return 0;
}
