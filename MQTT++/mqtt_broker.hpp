#ifndef broker


#include <iostream>
#include <forward_list>
#include <thread>

#include <chrono>
using namespace std::chrono;

#include "mqtt_server.hpp"
#include "mqtt_client.hpp"

namespace mqtt_broker{

class broker
{
    mqtt_broker::broker* host;
    std::forward_list<mqtt_client::client> subscribers;
public:
    broker(/* args */){};

    broker(mqtt_broker::broker* host): host(host){};
    ~broker(){};

    void set_host(mqtt_broker::broker* host_init){
        host = host_init;
    }

    void subscribe{mqtt_client}

    void start_broadcasting();
    void constant_broadcasting();
    void timeout_broadcasting();
};




void broker::start_broadcasting()
{

}

void broker::constant_broadcasting()
{

}

}

#endif // !broker