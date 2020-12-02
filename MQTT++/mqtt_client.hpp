#if !defined(CLIENT)  
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
#include "mqtt_message.hpp"
#include "mqtt_broker.hpp"

namespace mqtt_client{
//virtualizemos las funciones que hopefully
//van a ser utilizada a traves de todos los 
//hijos

class client_virtual
{   
    //Para no poder copiarse 
	client_virtual(const client_virtual&) =delete;
	client_virtual& operator=(const client_virtual&) =delete;
	

	/** unique ptr pero para mutexes */
	using unique_lock_mutex = std::unique_lock<std::mutex>;

    //mutex lock
    //mutable en vez de const
	mutable  std::mutex lock_client;

};


class client
{
public:
    client( mqtt_broker::broker *host_init, short ID)
            : _id(ID){host=host_init;};

    client(mqtt_broker::broker * host_init, short ID, std::string topic="/empty/")
            : _id(ID){host=host_init;};

    ~client(){};

    int connect(mqtt_broker::broker * host_init, short ID, std::string topic="/empty/");
    int publish(message mess);

    bool is_connected() const{
        return state;
    };    

    std::string get_topic() const{  
    return client_topic;};

    void _respuesta(mqtt_message::message* mess){};


private:
    bool state=false;
    unsigned int _id;
    std::string _name="";
    short _default_QoS=0;
    Clock _retry_in = std::chrono::seconds(1);
    
    //
    mqtt_broker::broker* host;
    std::string client_topic="";

};


int client::connect(mqtt_broker::broker * host_init, std::string topic="/empty/")
{   
    try
    {
        host= host_init;
        client_topic.assign(topic);
        state=mqtt::CONNECTED;
    }
    catch(mqtt_errors::error & e)
    {
        std::cout << e.what() << '\n';
    }

    return 0;

}
}//namespacen

#endif // CLIENT
