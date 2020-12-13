
#include <stdlib.h>
#include "mqtt_broker.cpp"

class client_wikipedia: public mqtt_client::client
{   std::string name="";
    
    public:
    client_wikipedia(){};

    void set_name(std::string n) {name.assign(n);}

    mqtt_message::message* reply(mqtt_message::message* mess)
    {
        std::cout<<"####Mensaje recibido por "<<name<<"####\n";
        std::cout<<"---La temperatura es "<<mess->get_payload()<< "----\n\n";
        return nullptr; //Podría devolver otro mensaje, pero no en este ejemplo
    };
}; 


int main(int argc, char const *argv[])
{   
    milliseconds m1 {5000};
    milliseconds m2 {1000};

    try
    {    
        mqtt_broker::broker servidor;

        servidor.set_timeout(m1);
        servidor.set_interval(m2);

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
        
        //Acá tiene que leer el mensaje anterior
        
        mqtt_message::message temperatur2("20 C", topic);
        servidor.publish_from(&clienteA, &temperatur2);

        mqtt_message::message temperatur3("38 C", "/temperature/roof/");
        servidor.publish_from(&clienteB, &temperatur3);
        
        servidor.disconnect(&clienteA);
        // servidor.disconnect(&clienteB);
        servidor.stop_broadcasting();
        
    }

    catch(mqtt_errors::error & e)
    {
        std::cout << e.what() << '\n';
    }
    
    return 0;
}
