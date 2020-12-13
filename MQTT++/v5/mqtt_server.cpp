#include <iostream>
#include <deque>
#include <forward_list>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "mqtt_server.hpp"

namespace mqtt_server{

    void server::set_timeout(milliseconds timeout_ms)
    { 
        server_timeout= timeout_ms;
    }

    void server::set_interval(milliseconds interval_ms)
    { 
        server_interval=interval_ms;
    }

    void server::append_message_from(void * cli, mqtt_message::message* mess)
    {   
        std::unique_lock<std::mutex> lock_broadcasting(server_mutex);

        if (get_deque_size() >= deque_max)
            broadcasting_condition.wait(lock_broadcasting);
            // throw mqtt_errors::MQTT_ERR_DEQUE();

        else
        {
            if (mess->get_QoS()==mqtt::NORMAL)
                message_deque.push_back({cli, mess});
            
            else if (mess->get_QoS()==mqtt::HIGH)
                message_deque.push_front({cli, mess});
            
            else
                throw mqtt_errors::MQTT_ERR_QOS();
        }
        // lock_broadcasting.unlock();

        //Si habia algun mensaje en espera para broadcast
        if (get_deque_size() == 1)
            broadcasting_condition.notify_one();

    }//append

    /*
    Esta funcion obtiene el mensaje top en la cola
    */
    publisher server::pop_message() 
    {
        publisher mess = message_deque.front();
        message_deque.pop_front();
        return mess;
    }

    /*
    Esta funcion obtiene el mensaje top en la cola
    verifica que la cola no este vacia. Si lo esta 
    devuelve nullptr
    */
    publisher server::get_message()
    {   
        if (get_deque_size()==0) 
            {   std::cout<<"Cola vacía.\n";
                return {nullptr, nullptr};
                }
                //throw mqtt_errors::MQTT_ERR_DEQUE_EMPTY();}
        else {
            std::cout<<"Mensajes en espera: "<<get_deque_size()-1<<std::endl;
            return pop_message();
        }

    }//broadcast

    void server::running_thread()
    {   
        broadcast_message();
        std::this_thread::sleep_for(server_interval);
    }

    void server::constant_broadcasting()
    {
        while (stop_thread==false) running_thread();
    }

    void server::timeout_broadcasting()
    {   
        auto now = system_clock::now();

        while (!stop_thread && (system_clock::now() - now ) < server_timeout )
            running_thread();
    }

    void server::start_broadcasting()
    {   
        if (server_timeout==null)
            server_thread = std::thread(&server::constant_broadcasting,this);
            
        else server_thread = std::thread(&server::timeout_broadcasting,this);
            
    }

    void server::stop_broadcasting()
    {   server_thread.join();
        stop_thread=true;
    }
}//namespae