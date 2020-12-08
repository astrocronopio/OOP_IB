#ifndef broker


#include <iostream>
#include <list>
#include <thread>
#include <string>

#include <chrono>
using namespace std::chrono;

#include "mqtt_server.cpp"
#include "mqtt_client.hpp"

namespace mqtt_broker{

class broker : public mqtt_server::server
{
private:
    std::list<mqtt_client::client *> subscribers;
    mqtt::id_generator ID_gen;

    //  Para no pisarme al conectar clientes
    std::condition_variable subscribers_condition;
    std::mutex  subscribers_mutex;
public:

    bool sin_subs() {return subscribers.empty();}
    
    //Publica el servidor a todos los clientes
    void publish(mqtt_message::message* mess);
    //Publica un cliente al servidor
    void publish_from(mqtt_client::client * cli, mqtt_message::message* mess);

    //Conecta el cliente la broker
    void connect(mqtt_client::client * cli, std::string topic);
    //Desconecta el cliente del servidor
    void disconnect(mqtt_client::client * cli);

    void broadcast_message();
};

}//namespace

#endif // !broker