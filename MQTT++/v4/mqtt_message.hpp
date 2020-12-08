#ifndef MESS


#include <iostream>
#include <string>
#include <algorithm>
#include <forward_list>
#include <stdlib.h>
#include <time.h>  
#include <chrono>

#include "mqtt.hpp"
#include "mqtt_errors.hpp"

namespace mqtt_message{ // porque me confundo entre libs, todas estan en
                        // un  namespace igual al .hpp

bool topic_match_sub(  const std::string topic_sub, 
                        std::forward_list<std::string> client_topic)
{   //Tengo que modificarla por si un cliente está conectado a mas topics
    for (auto topic_message : client_topic)
    {    
        if (topic_sub.compare(topic_message) == 0) 
            return true;

        else if (topic_sub.find(topic_message)!=std::string::npos)
            {   
                std::cout<<"\n";
                std::cout<< topic_message  <<" esta contenido en "<<topic_sub<<".\n";
                std::cout<<"\n";
                return true;
            }
    }
    
    return false;
}

using namespace std::chrono;
using Clock = std::chrono::high_resolution_clock::duration;

class message
{
private:
    std::string message_topic="";
    std::string payload;

    short QoS=mqtt::NORMAL; //Por defecto QoS es normal.
    bool published=false;
    bool retain=false;
    bool _published=false;
    bool _error= mqtt::MQTT_MESS_N0_SUCCESS;

public:
    //Const default
    message(){};

    //Const cambiando cosas
    message(std::string mes="", 
            std::string topic="",
            bool retain_=false ,
            short qos=mqtt::NORMAL
            )
            
            :message_topic(topic), 
            payload(mes)
            {QoS=qos; retain=retain_;};

    //Copy-Const
    ~message(){};

    std::string get_topic() const{  
        return message_topic;};

    std::string get_payload() const{  
        return payload;};

    bool is_retain() const{  
        return retain;};
    

    void set_topic(std::string topic){
        message_topic.assign(topic);};

    short get_QoS() const{ return QoS;}
    void set_QoS(short qos){QoS=qos;};

    void _wait_publish(){
        //Aca lockeo el proceso//
    }

    void _is_published(){
        //Acá  tengo que deslockear el proceso//
        if (mqtt::MQTT_MESS_SUCCESS ==_error)
            _published = true;
        
    }
};

}
#endif // !MESS