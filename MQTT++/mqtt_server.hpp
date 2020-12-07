#if !defined(SERVER)  
#define SERVER

#include <iostream>
#include <deque>
#include <forward_list>
#include <thread>
#include <mutex>
#include <condition_variable>

// std::mutex m;
// std::condition_variable mcond1;
// std::condition_variable mcond2;


#include <chrono>
using namespace std::chrono;
milliseconds null {0};
milliseconds ms1_2 {500};

#include "mqtt.hpp"
#include "mqtt_message.hpp"

namespace mqtt_server
{

/*
El publisher es un duo de mensaje y la direccion (ptr)
del cliente que mando el mensaje
*/
struct publisher{
    // void porque no quiero usar el ptr a cliente,
    // si lo hago genero una dependencia circular
    void * cli; 
    mqtt_message::message * mess;
};

/*
El servidor tiene el thread que lo corre como parte
de sus variables privadas. 

Tiene la opcion de agregar el timeout [server_timeout, 
server::set_timeout()] (cuanto tiempo esta prendido) y 
el intervalo entre mensajes[server_interval, server::
set_interval()]. Ambas variables estan en milisegundos.
*/

class server
{
private:
    std::deque< publisher > message_deque;
    unsigned int deque_max=10;
    
    duration<double,std::milli> server_timeout = null;
    duration<double,std::milli> server_interval = ms1_2;
    
    std::thread server_thread;
    std::mutex  server_mutex;
    std::condition_variable broadcasting_condition;

    bool stop_thread = false; // thread stopping.

    //No puedo copiar ni  mover el server
    //Me parecio oportuno porque no quiero modificar
    //Nada del servidor
    server(const server&) = delete;
    server& operator=(const server&) = delete;     

public:

    
    server():server_thread(){};
    server(unsigned int i): deque_max(i){};
    server(duration<double,std::milli> &rel_time): 
            server_timeout(rel_time){};
    
    void set_timeout(duration<double,std::milli> timeout_ms)
            { server_timeout=timeout_ms;};

    void set_interval(duration<double,std::milli> interval_ms)
            { server_interval=interval_ms;};

    ~server(){  };

    /////
    unsigned int  get_deque_size() const{ return message_deque.size(); };
    unsigned int  get_max_size()   const{ return deque_max; };
    
    void print_deque_size(){std::cout<<get_deque_size()<<std::endl;}

    /*
    Esta funcion obtiene el mensaje top en la cola
    */
    publisher pop_message() 
    {
        publisher mess = message_deque.front();
        message_deque.pop_front();
        return mess;
    }


    publisher get_message();
    
    //Es un mensaje para todos, entonces el cliente es nullptr
    void append_message(mqtt_message::message* mess)
    {
        append_message_from(nullptr, mess);
    };

    /*
    Esta funcion agrega el mensaje a la cola dependiendo de
    el QoS con el que viene el mensaje.
    */
    void append_message_from(void* cli, mqtt_message::message* mess);

    virtual void broadcast_message(){};
    void start_broadcasting();
    void constant_broadcasting();
    void timeout_broadcasting();
};


void server::append_message_from(void * cli, mqtt_message::message* mess)
{   
    if (get_deque_size() >= deque_max)
        throw mqtt_errors::MQTT_ERR_DEQUE();

    else
    {
        if (mess->get_QoS()==mqtt::NORMAL)
            message_deque.push_back({cli, mess});
        
        else if (mess->get_QoS()==mqtt::HIGH)
            message_deque.push_front({cli, mess});
        
        else
            throw mqtt_errors::MQTT_ERR_QOS();
    }
}//append

/*
Esta funcion obtiene el mensaje top en la cola
verifica que la cola no este vacia. Si lo esta 
devuelve nullptr
*/
publisher server::get_message()
{   
    std::cout<<get_deque_size()<<std::endl;

    if (get_deque_size()==0) 
        {   std::cout<<"Cola vacía.\n";
            return {nullptr, nullptr};
            }
            //throw mqtt_errors::MQTT_ERR_DEQUE_EMPTY();}
    else {   
        return pop_message();
    }

}//broadcast


void server::start_broadcasting()
{   if (server_timeout==null)
        {
            //server_thread = std::thread(&server::constant_broadcasting,this);
            // server_thread.detach();
            constant_broadcasting();
        }
       
    else
        {
            //server_thread = std::thread(&server::timeout_broadcasting,this);
            // server_thread.detach();
        }
        // timeout_broadcasting();
}

void server::constant_broadcasting()
{    std::cout<<"bro000";
    // std::unique_lock<std::mutex> lock_broadcasting(server_mutex);
    while (stop_thread==false)
    {   
        // std::unique_lock<std::mutex> lock_broadcasting(server_mutex);
        
        // std::this_thread::sleep_for(server_interval);
        std::this_thread::sleep_for(server_interval);
        broadcast_message();
    }
    
    // broadcasting_condition.wait(lock_broadcasting)
    
}

void server::timeout_broadcasting()
{   
    // while (!stop_thread)
    // {   std::lock_guard<std::mutex> lock_br(server_mutex);
    //     std::this_thread::sleep_for(server_interval);
    //     std::cout << "good morning" << std::endl;
    // }
}


}//namespace end

#endif // !SERVER