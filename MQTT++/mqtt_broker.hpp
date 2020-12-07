#ifndef broker


#include <iostream>
#include <list>
#include <thread>
#include <string>

#include <chrono>
using namespace std::chrono;

#include "mqtt_server.hpp"
#include "mqtt_client.hpp"

namespace mqtt_broker{

class broker : public mqtt_server::server
{
    std::list<mqtt_client::client *> subscribers;
    mqtt::id_generator ID_gen;

public:
    broker(){};
    
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

    void broker::publish(mqtt_message::message* mess)
    {
        append_message(mess);
    }

    void broker::publish_from(mqtt_client::client * cli, mqtt_message::message* mess)
    {   
        append_message_from(cli, mess);
    }

    void broker::broadcast_message(){ 
       
        bool flag = false;
        mqtt_server::publisher pub_mess = get_message();
        mqtt_message::message* client_reply = nullptr;

        for (mqtt_client::client *i : subscribers)
        {   
            //no puede mandarse un mensaje a si mismo
            if (i == (mqtt_client::client *) pub_mess.cli ) 
                continue; 
             
            //Si encuentra un match de topic, manda el mensaje
            if (mqtt_message::topic_match_sub(pub_mess.mess->get_topic(), i->get_topic()))
                {  flag=true;

                   client_reply = i->reply(pub_mess.mess);
                   if (client_reply!=nullptr) 
                        publish_from(i, client_reply);
                }
        }
        /*Si nadie recibio el mensaje y  tiene el flag de retain
        lo pone nuevamente en la cola de mensajes
        */
        if (pub_mess.mess!=nullptr &&
            flag==false && //Si se leyó o no
            pub_mess.mess->is_retain()) //Si se debe retener o no

            append_message_from(pub_mess.cli, pub_mess.mess);
    }

    void broker::connect(mqtt_client::client * cli, std::string topic)
    {
        if (cli->isConnected()==true)
        {
            std::cout<<"El cliente "<< cli->get_id()<< "ya está conectado a un server";
            return;
        }
        else
        {   
            cli->set_id(ID_gen.Random_ID());
            cli->Connect();
            cli->subscribe(topic);
            subscribers.push_front(cli);
        }

    }

    void broker::disconnect(mqtt_client::client * cli)
    {   
        cli->set_id(0);
        cli->Disconnect();
        subscribers.remove(cli);
    }

}//namespace

#endif // !broker