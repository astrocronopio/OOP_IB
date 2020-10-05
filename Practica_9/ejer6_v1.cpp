/*
Ejercicio 6 de la guia 9 de la materia de 
OPP C++ del Instituto Balseiro, Agosto 2020

Escrito por Evelyn Coronel
*/
#include <iostream>

template<typename T>
class UniquePtr
{
private:
    T* pointer;

    //No puede copiarse 
    UniquePtr( const UniquePtr<T>& dummy) = delete;
    UniquePtr<T>& operator=(const UniquePtr<T>& dummy) = delete;
public:
    //Init unique ptr
    UniquePtr(T& init_var):pointer(&init_var){};

    //Para moverse 
    
    // T* move(T* dummy) no hace falta, asumo 
    // que la clase T ya tiene implemetado esto
    // {
    //     using std::move;
    //     swap(a1.array,a2.array);
    // }

    UniquePtr(UniquePtr<T>& dummy)
    {
       pointer = std::move(dummy.pointer);// Es más rápido que el swap
       dummy.pointer = nullptr;
    };
    
    UniquePtr<T>& operator=(UniquePtr<T>&& dummy) 
    {
       if (this == dummy) return *this;
       pointer = std::move(dummy.pointer);// Es más rápido que el swap
       dummy.pointer = nullptr;
       return *this;
    }
    ~UniquePtr(){ delete pointer;};

    void print() const { std::cout<<(void *) pointer<< std::endl;};

};


int main(int argc, char const *argv[])
{   
    int a=1;
    UniquePtr<int> ptr_a(a);
    std::cout<<"\nPtr_a\n";
    std::cout<<(void *) &a<< std::endl;
    ptr_a.print();

    std::cout<<"\nPtr_b\n";
    UniquePtr<int> ptr_b = ptr_a;
    ptr_b.print();


    return 0;
}
