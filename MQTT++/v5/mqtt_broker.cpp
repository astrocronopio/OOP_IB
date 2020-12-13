#include <iostream>
#include <list>
#include <thread>
#include <string>

#include <chrono>
using namespace std::chrono;

#include "mqtt_broker.hpp"

namespace mqtt_broker
{
    void broker::publish(mqtt_message::message* mess)
    {
        append_message(mess);
    }

    void broker::publish_from(mqtt_client::client * cli, mqtt_message::message* mess)
    {   
        append_message_from(cli, mess);
    }

    void broker::broadcast_message()
    {   
        std::unique_lock<std::mutex> lock_broadcasting(server_mutex);

        if (get_deque_size() == 0)
            {
                std::cout<<"Cola de mensajes vacía\n";
                broadcasting_condition.notify_one();
                return;
            }
        
        if (sin_subs())
            {
                std::cout<<"No hay clientes conectados\n";
                return;
            }


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
           { publish_from((mqtt_client::client *) pub_mess.cli, pub_mess.mess);}
        

        /*
        Si  hay algun mensaje esperando ser publicado
        */
        if (get_deque_size() == (get_max_size()-1))
            broadcasting_condition.notify_one();
    }

    void broker::connect(mqtt_client::client * cli, std::string topic)
    {   
        std::unique_lock<std::mutex> lock_sub(subscribers_mutex);

        bool was_empty = sin_subs();

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

        lock_sub.unlock();

        if (was_empty)
            subscribers_condition.notify_one();
    }

    void broker::disconnect(mqtt_client::client * cli)
    {   std::unique_lock<std::mutex> lock_sub(subscribers_mutex);
        std::unique_lock<std::mutex> lock_broadcasting(server_mutex);

        if (get_deque_size()>0)
            broadcasting_condition.wait(lock_broadcasting);

        if (sin_subs()) 
            subscribers_condition.wait(lock_sub);

        cli->set_id(0);
        cli->Disconnect();
        subscribers.remove(cli);
    }
}