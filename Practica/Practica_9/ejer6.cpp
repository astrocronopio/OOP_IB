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

    UniquePtr( const UniquePtr<T>& dummy) = delete;
    UniquePtr<T>& operator=(const UniquePtr<T>& dummy) = delete;

public:
    //Init unique ptr
    UniquePtr(T* init_var):pointer(new T){
        *pointer = *init_var;
    };

    friend void swap(UniquePtr& a1, UniquePtr& a2)
    {
        using std::swap;
        a1.pointer=nullptr;
        swap(a1.pointer,a2.pointer);
        a2.pointer=nullptr;
        delete a2.pointer;
    };

    UniquePtr(UniquePtr<T>& dummy)
    {
       swap(*this, dummy);
    };
    
    UniquePtr<T>& operator=(UniquePtr<T> dummy) 
    {
       if (this == dummy) return *this;
       swap(pointer,dummy.pointer);
       return *this;
    }

    T* operator->(){return pointer;};
    T& operator*(){return *pointer;};

    ~UniquePtr(){delete pointer;};

    void print() const { std::cout<<(void *) pointer;};

};


int main(int argc, char const *argv[])
{   
    int a=1;
    UniquePtr<int> ptr_a(&a);
    std::cout<<"\nPtr_a : @";
    ptr_a.print();
    std::cout<<" con valor "<< *ptr_a;
    //std::cout<< (void*) ptr_a->(pointer);

    UniquePtr<int> ptr_b = ptr_a;
    std::cout<<"\nPtr_b (al mover a -> b): @";
    ptr_b.print();
    std::cout<<" con valor "<< *ptr_b;

    std::cout<<"\nPtr_a despues de moverse: @";
    ptr_a.print();

    *ptr_b=2;
    std::cout<<"\nPtr_b tras reasignar valor: @";
    ptr_b.print();
    std::cout<<" con valor "<< *ptr_b;


    std::cout<<std::endl;

    return 0;
}
