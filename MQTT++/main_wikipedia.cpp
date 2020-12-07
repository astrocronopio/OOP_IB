
#include <stdlib.h>

#include "mqtt_client.hpp"
#include "mqtt_broker.hpp"


class client_wikipedia: public mqtt_client::client
{   std::string name="";
    
    public:
    client_wikipedia(){};

    void set_name(std::string n) {name.assign(n);}

    mqtt_message::message* reply(mqtt_message::message* mess)
    {
        std::cout<<"Mensaje recibido por "<<name<<":\n";
        std::cout<<"La temperatura es "<<mess->get_payload()<<std::endl;
        return nullptr; //Podría devolver otro mensaje, pero no en este ejemplo
    };
}; 


int main(int argc, char const *argv[])
{   

    try
    {    
        mqtt_broker::broker servidor;
        servidor.start_broadcasting();

        client_wikipedia clienteB;
        clienteB.set_name(" client B ");

        std::string topic="/temperature/roof/";

        servidor.connect(&clienteB, topic);
        mqtt_message::message temperatura("25 C", topic, true);
        servidor.publish_from(&clienteB, &temperatura);

        client_wikipedia clienteA;
        clienteA.set_name(" client A ");

        servidor.connect(&clienteA, topic);
        
        servidor.print_deque_size();
        //Acá tiene que leer el mensaje anterior
        
        mqtt_message::message temperatur2("20 C", topic);
        servidor.publish(&temperatura);

        mqtt_message::message temperatur3("38 C", "/temperature/roof/");
        servidor.publish(&temperatura);
        
        //A recibe

        servidor.disconnect(&clienteA);
        servidor.disconnect(&clienteB);

        servidor.print_deque_size();
        
    }

    catch(mqtt_errors::error & e)
    {
        std::cout << e.what() << '\n';
    }
    
    return 0;
}
