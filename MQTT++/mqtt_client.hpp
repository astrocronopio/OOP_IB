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
    virtual void reply(mqtt_message::message* mess)=0;

    virtual bool isConnected() const =0;
    virtual void Connect() = 0;
    virtual void Disconnect() =0;
    
    private:
    //Para no poder copiarse 
	client_virtual(const client_virtual&) =delete;
	client_virtual& operator=(const client_virtual&) =delete;
};


class client : public client_virtual
{
public:

    client(){}; //Random ID, es malo esta forma porque no 
                    // me aseguro que no haya

    void set_id(unsigned int  ID){id=ID;};
    unsigned int get_id() const {return id;};

    void subscribe(std::string topic) {client_topic.push_front(topic);};
    
    std::forward_list<std::string> get_topic() const{ return client_topic;};
    virtual void reply(mqtt_message::message* mess)=0;

    bool isConnected() const {return Connected;}
    void Connect() { Connected=true;}
    void Disconnect() { Connected=false;}

private:
    bool Connected=false;
    unsigned int id=0;
    std::string name="";
    short default_QoS=0;
    std::forward_list<std::string> client_topic;

};


}//namespacen

#endif // CLIENT
