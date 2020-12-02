#include <iostream>
#include <stdlib.h>


#include "mqtt.hpp"
#include "mqtt_errors.hpp"
#include "mqtt_message.hpp"
#include "mqtt_broker.hpp"
#include "mqtt_client.hpp"



int main(int argc, char const *argv[])

    try
    {   
        mqtt_broker::broker servidor();

        mqtt_client::client clienteB();

        clienteB.connect(servidor);
        mqtt_message::message temperatura("25 C", "/temperature/roof/");
        clienteB.publish(temperatura);

        mqtt_client::client clienteA();
        clienteB.connect(servidor);
        //Acá tiene que leer el mensaje anterior
        
        mqtt_message::message temperatur2("20 C", "/temperature/roof/");
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
