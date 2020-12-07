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

// struct subscriber{
//     mqtt_client::client * cli;
//     unsigned int ID;
// };


class broker : public mqtt_server::server
{
    std::list<mqtt_client::client *> subscribers;
    mqtt::id_generator ID_gen;
public:
    broker(){};
    
    void publish(mqtt_message::message* mess);
    void publish_from(mqtt_client::client * cli, mqtt_message::message* mess);

    void connect(mqtt_client::client * cli, std::string topic);
    void disconnect(mqtt_client::client * cli);

    void broadcast_message(mqtt_client::client * publisher);

};

    void broker::publish(mqtt_message::message* mess)
    {
        append_message(mess);
    }

    void broker::publish_from(mqtt_client::client * cli, mqtt_message::message* mess)
    {   
        append_message(mess);
    }

    void broker::broadcast_message(mqtt_client::client * publisher = nullptr)
    {   
        bool flag = false;
        mqtt_message::message* mess = pop_message();
        mqtt_message::message* client_reply = nullptr;
        
        for (auto i : subscribers)
        {   
            if (i == publisher) continue; // no se puede mandar un mensaje a si mismo

            if (mqtt_message::topic_match_sub(mess->get_topic(), i->get_topic()))
                {  flag=true;

                   client_reply = i->reply(mess);
                   if (client_reply!=nullptr) 
                        publish_from(i, client_reply);
                }
        }
        if (flag==false && mess->is_retain())
            append_message(mess);
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