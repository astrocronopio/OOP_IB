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
#include "mqtt_client.hpp"

namespace mqtt_broker
{


class broker
{
private:
    std::deque<mqtt_message::message> message_deque;
    std::forward_list<mqtt_client::client*> clients_list;
    unsigned int deque_max=10;

    duration<double,std::milli> server_timeout=0;

public:
    broker(){};
    broker(unsigned int i): deque_max(i){};
    broker(duration<double,std::milli> &rel_time): server_timeout(time_out){};
    
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

    short connect_client(mqtt_client::client* cli);
    void broadcast_message();
    void disconnect_client(mqtt_client::client* cli);
    void disconnect_client(short ID);
    void disconnect_client(std::string topic_cli);

    void start_broadcasting();
    void constant_broadcasting();
    void timeout_broadcasting();

    
    

};


void broker::append_message(mqtt_message::message mess)
{   
    if (message_deque.size() => deque_max):
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


short broker::connect_client(mqtt_client::client* cli )
{
    clients_list.push_front(cli);
    return mqtt::CONNACK;
    
}//append_mess

void broker::broadcast_message()
{   
    if (message_deque.size()==0) 
        throw mqtt_errors::MQTT_ERR_DEQUE_EMPTY();
    
    bool flag=false;

    mqtt_message::message* mess = message_deque.pop_front();

    for (auto client_prt : clients_list) 
    {
        if (topic_match_sub(client_prt->get_topic(), mess->get_topic())
            {   flag=true;
                try
                {
                    client_prt->_respuesta(mess);
                }
                catch(const mqtt_errors::error& e)
                {
                    std::cerr << e.what() << '\n';
                }
                
            }
    }

    if (flag==false) 
        throw mqtt_errors::MQTT_ERR_MESS();
    
}//broadcast



void broker::start_broadcasting()
{
    if server_timeout==-1
    {
        constant_broadcasting();
    }
    else 
    {
        timeout_broadcasting();
    }
}

void broker::constant_broadcasting()
{

}

broker::disconnect_client(mqtt_client::client* cli)
{


}//disconnect cli

broker::disconnect_client(short ID)
{


}//disconnect ID

broker::disconnect_client(std::string topic_cli)
{


}//disconnect cli


}//namespace end

#endif // !BROKER