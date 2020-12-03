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

// #include "mqtt_broker.hpp"

namespace mqtt_client{


class client_virtual
{   
    public:
    client_virtual();
    ~client_virtual();
    //Para no poder copiarse 
	client_virtual(const client_virtual&) =delete;
	client_virtual& operator=(const client_virtual&) =delete;
	

	/** unique ptr pero para mutexes */
	using unique_lock_mutex = std::unique_lock<std::mutex>;

    //mutex lock
    //mutable en vez de const
	mutable  std::mutex lock_client;


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
        try
        {
            host = host_init;
            client_topic.push_front(topic);
            
            // if( host->connect_client(this) != mqtt::CONNACK) 
            //     throw mqtt_errors::MQTT_ERR_CONNACK();

            state=mqtt::CONNECTED;
        }
        catch(mqtt_errors::error & e)
        {
            std::cout << e.what() << '\n';
        }
    }; //connect


    client( mqtt_broker::broker *host_init)
            {host=host_init;};

    int publish(mqtt_message::message  mess)
    {
        host->append_message(mess);
    };
    int disconnect();

    bool is_connected() const{
        return state;
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
