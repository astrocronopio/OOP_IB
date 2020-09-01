#ifndef STACK_H
#define STACK_H 1

#include <iostream>

class Stack
{
	std::string *v;
	int top, max_size;

public
    Stack(int s){
	    top=0;
	    if (s<=0 || s>1000) throw Bad_size{};
	    max_size = s;
	    std::cout<<"Se creó un stack con lugar para "<<max_size<<" elementos.\n";
    	v= new std::string[s];
        };

	~Stack(){delete [] v;};

	class Underflow{ };
	class Overflow{ };
	class Bad_size{ };

    void push(std::string c)
    {
    	if (top == max_size) throw Overflow{};
    	v[top++] = c;
    	std::cout << "Pushing \'" << c << ". ";
    	std::cout << " Quedan " << max_size - top <<" de "<<max_size << " lugares.\n";
    };
    
    std::string pop()
    {
    	if( top == 0) throw Underflow{};
    	top--;
    	std::cout << "Poping \'" << v[top] <<"\n";
    	return v[top];
    };

	friend std::ostream &operator<<(std::ostream &os, const Stack &stack_dummy)
	{	if (stack_dummy.top==0) os<<"\nEl stack está vacío.\n\n";
		else {
			os<<  "\nImprimiendo el stack :\n__Stack__\n\n";
			for (int i = stack_dummy.top-1; i >= 0 ; i--)
				os<<"Orden "<< i+1 <<"/"<<stack_dummy.max_size<<":"<< stack_dummy.v[i]<< "\n";
			os<<"_________\n\n";}
		return os;	
	} 

    //#######################################
    Stack(int s, std::string* p)
    {
        top=0;
	    if (s<=0 || s>1000) throw Bad_size{};
	    max_size = s;
	    std::cout<<"Se creó un stack con lugar para "<<max_size<<" elementos.\n";
    	v= new std::string[s];

        for (int i = 0; i < s; i++)
            v[top++]=p[i];
    };
    //#######################################
};

#endif // !STACK_H 