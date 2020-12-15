
#include <stdlib.h>
#include "mqtt_broker.cpp"

class client_qos: public mqtt_client::client
{   private:
    bool on = mqtt::OFF;
    std::string name="";
    
    public:
    client_qos(){on=mqtt::ON;};

    void set_on(bool switch_){on=switch_;};

    void set_name(std::string n) {name.assign(n);}

    mqtt_message::message* reply(mqtt_message::message* mess)
    {   
        std::cout<<"####Mensaje recibido por "<<name<<" con QoS: "<<mess->get_Priority()<<"####\n";
        std::cout<<"---"<<mess->get_payload()<< "----\n\n";

        if (mess->get_payload()=="OFF")
            {   
                std::string reply_payload = "Soy " + name + " y me apagué";

                mqtt_message::message* reply_message = 
                                    new mqtt_message::message(reply_payload, mess->get_topic(), mess->is_retain());
                
                set_on(mqtt::OFF); 

                return reply_message; //Responde que se apagó
            }
        else {mess = nullptr; delete mess;}

        return nullptr; 
    };
}; 


int main(int argc, char const *argv[])
{   
    milliseconds m2 {500};

    try
    {    
        mqtt_broker::broker servidor;

        servidor.set_interval(m2);

        servidor.start_broadcasting();

        client_qos clienteB;
        clienteB.set_name(" luz B ");

        std::string topic="/luz/roof/";

        servidor.connect(&clienteB, topic);

        client_qos clienteA;
        clienteA.set_name(" luz A ");

        servidor.connect(&clienteA, topic);
        
        //Acá tiene que leer el mensaje anterior
        
        mqtt_message::message mess2("ON", topic);
        servidor.publish_from(&clienteA, &mess2);

        mqtt_message::message mess3("OFF", topic, false, mqtt::HIGH);
        servidor.publish_from(&clienteB, &mess3);
        
        // servidor.disconnect(&clienteA);
        // servidor.disconnect(&clienteB);
        servidor.stop_broadcasting();
        
    }

    catch(mqtt_errors::error & e)
    {
        std::cout << e.what() << '\n';
    }
    
    return 0;
}