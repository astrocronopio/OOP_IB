#if !defined(SERVER)  
#define SERVER

#include <iostream>
#include <deque>
#include <forward_list>
#include <thread>

#include <chrono>
using namespace std::chrono;

#include "mqtt.hpp"
#include "mqtt_message.hpp"

namespace mqtt_server
{

class server
{
private:
    std::deque<mqtt_message::message> message_deque;
    unsigned int deque_max=10;
    // duration<double,std::milli> server_timeout;

public:
    server(){};
    server(unsigned int i): deque_max(i){};
    // server(duration<double,std::milli> &rel_time): server_timeout(rel_time){};
    
    ~server(){};

    //No puedo copiar ni  mover el server
    //Me parecio oportuno porque no quiero modificar
    //Nada del servidor

    server(const server&) = delete;
    server& operator=(const server&) = delete;

    /////
    unsigned int get_deque_size() const{ return message_deque.size(); };

    unsigned int  get_max_size() const{ return deque_max; };

    void append_message(mqtt_message::message mess);

    void broadcast_message();


};


void server::append_message(mqtt_message::message mess)
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


void server::broadcast_message()
{
    bool flag=false;
    if (message_deque.size()==0) 
        throw mqtt_errors::MQTT_ERR_DEQUE_EMPTY();
    
    if (flag==false) 
        throw mqtt_errors::MQTT_ERR_MESS();
    
}//broadcast



}//namespace end

#endif // !SERVER