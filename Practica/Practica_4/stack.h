#ifndef STACK_H
#define STACK_H 1

#include <iostream>
#include <vector>


class Stack
{
	std::string* *v;
	int top, max_size;

public:
    Stack(int s)
    {
	    top=0;
	    if (s<=0 || s>1000) throw Bad_size{};
	    max_size = s;
	    std::cout<<"Se creó un stack con lugar para "<<max_size<<" elementos.\n";
    	v= new std::string*[s];
    };

	~Stack(){delete [] v;};

	class Underflow{ };
	class Overflow{ };
	class Bad_size{ };

    void  push(std::string* c);
	std::string pop();

	friend std::ostream &operator<<(std::ostream &os, const Stack &stack)
	{	
        if (stack.top==0) os<<"\nEl stack está vacío.\n\n";
		else {
			os<<  "\nImprimiendo el stack :\n__Stack__\n\n";
			for (int i = stack.top-1; i >= 0 ; i--)
				os<<"Orden "<< i+1 <<"/"<<stack.max_size<<":"<< *(stack.v[i])<< "\n";
			os<<"_________\n\n";}
		return os;	
	} 

    //#######################################
    Stack(int s, std::vector <std::string*> p)
    {
        top=0;
	    if (s<=0 || s>1000) throw Bad_size{};
	    max_size = s;
	    std::cout<<"Se creó un stack con lugar para "<<max_size<<" elementos.\n";
    	v= new std::string*[s];

        for (int i = 0; i < s; i++)
            v[top++]=p[i];
    };
    //#######################################
};

#endif // !STACK_H 