#include "iostream"

template <typename T>
class List//: public Link
{
public:
    T value;
    List* Next;
    
    List(T valor): value(valor), Next(nullptr){   };
    
    void add( T valor)
    {
        List<T> * new_list = (List<T> *)  new List<T>(valor);
        List<T> * aux_ptr= this;

        while (aux_ptr->Next!=nullptr)
            aux_ptr=aux_ptr->Next;

        aux_ptr->Next=new_list;

        // List<T> *aux_ptr= Next;

        // while ((aux_ptr)!=nullptr)
        //     aux_ptr=(aux_ptr)->Next;

        // aux_ptr=new_list;
    };
    
    void print(){
        List<T> * aux_ptr= this;

        std::cout<<aux_ptr->value<<"\t";
        std::cout<<(void *)aux_ptr<<std::endl;

        while (aux_ptr->Next!=nullptr)
        {   aux_ptr= aux_ptr->Next;
            std::cout<<aux_ptr->value<<"\t";
            std::cout<<(void *)aux_ptr<<std::endl;
        } 
    };
};



int main(int argc, char const *argv[])
{   
    int a=1;
    List<int> pepe(1);
    std::cout<<"El primero\n";
    pepe.print();

    std::cout<<"El 2o\n";
    pepe.add(2);
    pepe.print();

    std::cout<<"El 3o\n";
    pepe.add(3);
    pepe.print();

    std::cout<<"El 4o\n";
    pepe.add(4);
    pepe.print();

    return 0;
}
