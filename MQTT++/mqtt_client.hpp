#ifndef CLIENT
#define CLIENT


#include <iostream>
#include <string>
#include <algorithm>

#include <stdlib.h>
#include <time.h>  
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "mqtt.hpp"
#include "mqtt_errors.hpp"

#include "mqtt_broker.hpp"

namespace mqtt_client{


class client_virtual
{   
    public:
    client_virtual(){};
    ~client_virtual(){};
    //Para no poder copiarse 
	client_virtual(const client_virtual&) =delete;
	client_virtual& operator=(const client_virtual&) =delete;
};


class client : public client_virtual
{
public:
    client(){};
    client( mqtt_broker::broker *host_init)
            {host=host_init;};

//     client( mqtt_broker::broker *host_init, short ID)
//             : _id(ID){host=host_init;};

//     client(mqtt_broker::broker * host_init, short ID, std::string topic="/empty/")
//             : _id(ID){host=host_init;};


    void  connect(mqtt_broker::broker * host_init, std::string topic="/empty/")
    {   

    }; //connect

    void  disconnect()
    {   

    }; //connect


    void publish(mqtt_message::message  mess)
    {
        
    };    

    std::forward_list<std::string> get_topic() const{  
    return client_topic;};

    void _respuesta(mqtt_message::message* mess){};


private:
    bool state=false;
    unsigned int _id;
    std::string _name="";
    short _default_QoS=0;
    // mqtt::Clock _retry_in = std::chrono::seconds(1);
    
    
    mqtt_broker::broker* host;
    std::forward_list<std::string> client_topic;

};


}//namespacen

#endif // CLIENT
