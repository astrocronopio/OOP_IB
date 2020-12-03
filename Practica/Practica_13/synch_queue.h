#ifndef SYNCH
#define SYNCH

#include <iostream>
#include <thread>
#include <array>

#include <chrono>

#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable mcond1;
std::condition_variable mcond2;

using namespace std::chrono;

template<class T, size_t N>  
class Queue 
{   private:
    std::array<T,N> data;
    size_t queue_tail=0;
    
    public:    

    size_t get_tail() const {return queue_tail;};
    size_t get_capacity() const {return data.size();};

    void print(std::string comment = ""){
        std::unique_lock<std::mutex> lck{m};
        
        std::cout<<"\n"<<comment<<std::endl;
        std::cout<<"\n__Print Synch Queue__\n";
        
        for (size_t i = 0; i < this->get_tail(); i++)        
            std::cout<<data[i]<<std::endl;
        std::cout<<"''''''''''''\n";
    }

    void put(const T& value)
    {   
        if (this->get_tail() >= this->get_capacity()) 
            throw std::length_error("Fuera de límite (queue_tail=max_value)");
        else
        {
        data[queue_tail]=value;
        std::cout<<"Agregamos <<"<<value<<">>\n";
        queue_tail++;
        }
    };  
    void get()
    {   
        if (this->get_tail()<=0) 
            throw std::length_error("Fuera de límite (queue_tail=0)");
        else
        {
        queue_tail--;
        std::cout<<"Sacamos <<"<<data[queue_tail]<<">>"<<std::endl;
        }
    };
    //
    
    bool try_put(const T& value)
    {   
        try
        {
            put(value);
        }
        catch(const std::length_error& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
        return true;
    };    
    bool try_get()
    {   
        try
        {
            get();
        }
        catch(const std::length_error& e)
        {
            std::cerr << e.what() << '\n';
            return false;
        }
        return true;
    };         
    //

    template <class Rep, class Period>         
    bool try_put_for(const T& value, const duration<Rep,Period> &rel_time)
    {   
        std::unique_lock<std::mutex> lck{m};

        if (try_put(value)==false)
        {
            mcond1.wait_for(lck, rel_time);
            return try_put(value);
        }
        else 
        {
            mcond1.notify_one();    
            return true;
        }
    };

    //
    template <class Clock, class Duration>         
    bool try_put_until(const T& value, const time_point<Clock,Duration> &abs_time)
    {
        std::unique_lock<std::mutex> lck{m};
        
        if (try_put(value)==false)
        {
            mcond2.wait_until(lck, abs_time);
            return try_put(value);
        }
        else 
        {
            mcond2.notify_one();    
            return true;
        }
    };       

    template <class Rep, class Period>         
    bool try_get_for(const duration<Rep,Period> &rel_time)
    {   
        std::unique_lock<std::mutex> lck{m};

        if (try_get()==false)
        {
            mcond1.wait_for(lck, rel_time);
            return try_get();
        }
        else 
        {
            mcond1.notify_one();    
            return true;
        }
    };       
    
    template <class Clock, class Duration>         
    bool try_get_until(const time_point<Clock,Duration> &abs_time)
    {   
        std::unique_lock<std::mutex> lck{m};
        if (try_get()==false)
        {
            mcond2.wait_until(lck, abs_time);
            return try_get();
        }
        else 
        {
            mcond2.notify_one();    
            return true;
        }
    };  
};


#endif // !SYNCH