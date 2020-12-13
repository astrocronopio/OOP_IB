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
#include "mqtt_server.hpp"

namespace mqtt_client{


class client_virtual
{   
    public:
    client_virtual(){};
    ~client_virtual(){};

    virtual void subscribe(std::string topic) =0;
    virtual bool isConnected() const =0;
    virtual void Connect() = 0;
    virtual void Disconnect() =0;
    
    /*
    La función client::reply() debe ser implementado por cada 
    tipo de cliente, ya  que cada uno va a tener un tipo de 
    respuesta distinta.
    */

    virtual mqtt_message::message* reply(mqtt_message::message* mess)=0;

    private:
    //Para no poder copiarse 
	client_virtual(const client_virtual&) =delete;
	client_virtual& operator=(const client_virtual&) =delete;
};

/*
El cliente solo puede estar conectado a un servidor
al mismo tiempo.
Tiene la opcion de hacer que sus mensajes siempre vayan
al inicio de la cola de mensajes con  Priority=HIGH.

La función client::reply() debe ser implementado por cada 
tipo de cliente, ya  que cada uno va a tener un tipo de 
respuesta distinta.
*/
class client : public client_virtual
{
public:

    client(){};

    void set_id(unsigned int  ID){id=ID;};
    unsigned int get_id() const {return id;};

    void set_Priority(short priority){default_Priority=priority;};

    void subscribe(std::string topic) {client_topic.push_front(topic);};
    
    std::forward_list<std::string> get_topic() const{ return client_topic;};

    bool isConnected() const {return Connected;}
    void Connect() { Connected=mqtt::CONNECTED;}
    void Disconnect() { Connected=mqtt::DISCONNECTED;}

private:
    bool Connected=mqtt::DISCONNECTED;
    unsigned int id=0;
    std::string name="";
    short default_Priority=mqtt::NORMAL;
    std::forward_list<std::string> client_topic;
};


}//namespacen

#endif // CLIENT
