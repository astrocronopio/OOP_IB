#include <iostream>
#include <stdlib.h>

#include "mqtt_client.hpp"

class client_wikipedia: public mqtt_client::client
{
    public:
    client_wikipedia(){};
};


int main(int argc, char const *argv[])
{
    try
    {   
        mqtt_broker::broker servidor;

        client_wikipedia clienteB;

        std::string topic="/temperature/roof/";

        clienteB.connect(&servidor, topic);
        mqtt_message::message temperatura("25 C", topic);
        clienteB.publish(temperatura);

        client_wikipedia clienteA;
        clienteA.connect(&servidor, topic);
        
        //Acá tiene que leer el mensaje anterior
        
        mqtt_message::message temperatur2("20 C", topic);
        clienteA.publish(temperatura);

        mqtt_message::message temperatur3("38 C", "/temperature/roof/");
        clienteB.publish(temperatura);
        
        //A recibe

        clienteA.disconnect();
    }

    catch(mqtt_errors::error & e)
    {
        std::cout << e.what() << '\n';
    }
    
    return 0;
}
