#if !defined(BROKER)  
#define BROKER

#include <iostream>
#include <deque>
#include <forward_list>
#include <thread>

#include <chrono>
using namespace std::chrono;

#include "mqtt.hpp"
#include "mqtt_message.hpp"

namespace mqtt_broker
{


class broker
{
private:
    std::deque<mqtt_message::message> message_deque;
    unsigned int deque_max=10;
    duration<double,std::milli> server_timeout;

public:
    broker(){};
    broker(unsigned int i): deque_max(i){};
    broker(duration<double,std::milli> &rel_time): server_timeout(rel_time){};
    
    ~broker(){};

    //No puedo copiar ni  mover el broker
    //Me parecio oportuno porque no quiero modificar
    //Nada del servidor

    broker(const broker&) = delete;
    broker& operator=(const broker&) = delete;

    /////
    unsigned int get_deque_size() const{ return message_deque.size(); };

    unsigned int  get_max_size() const{ return deque_max; };

    void append_message(mqtt_message::message mess);

    void broadcast_message();

    void start_broadcasting();
    void constant_broadcasting();
    void timeout_broadcasting();

    
    

};


void broker::append_message(mqtt_message::message mess)
{   
    if (message_deque.size() >= deque_max)
        throw mqtt_errors::MQTT_ERR_DEQUE();

    else
    {
        if (mess.get_QoS()==mqtt::NORMAL)
            message_deque.push_back(mess);
        
        else if (mess.get_QoS()==mqtt::HIGH)
            message_deque.push_front(mess);
        
        else
            throw mqtt_errors::MQTT_ERR_QOS();
    }
}//append


void broker::broadcast_message()
{
    bool flag=false;
    if (message_deque.size()==0) 
        throw mqtt_errors::MQTT_ERR_DEQUE_EMPTY();
    


    if (flag==false) 
        throw mqtt_errors::MQTT_ERR_MESS();
    
}//broadcast



void broker::start_broadcasting()
{

}

void broker::constant_broadcasting()
{

}


}//namespace end

#endif // !BROKER