#if !defined(SERVER)  
#define SERVER

#include <iostream>
#include <deque>
#include <forward_list>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <chrono>
using namespace std::chrono;
milliseconds null {0};
milliseconds ms1_2 {100};

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

Tiene la opcion de agregar el timeout  [server_timeout, 
server::set_timeout<duration>()] (cuanto tiempo esta prendido) y 
el intervalo entre mensajes[server_interval, server::
set_interval()] en milisegundos.  El timeout tiene un mínimo
de 1 milisegundo
*/

class server
{
protected:
    std::condition_variable broadcasting_condition;
    std::thread server_thread;
    std::mutex  server_mutex;

private:
    std::deque< publisher > message_deque;
    unsigned int deque_max=10;
    
    milliseconds server_timeout = null;
    milliseconds server_interval = ms1_2;

    bool stop_thread = false; // thread stopping.

    //No puedo copiar ni  mover el server
    //Me parecio oportuno porque no quiero modificar
    //Nada del servidor
    server(const server&) = delete;
    server& operator=(const server&) = delete;     

public:

    
    server():server_thread(){};
    server(unsigned int i): deque_max(i){};
    server(milliseconds &rel_time): 
              server_timeout(rel_time){};
    ~server(){};

    /////
    void set_timeout(milliseconds timeout_ms);
    void set_interval(milliseconds interval_ms);

    unsigned int  get_deque_size() const{ return message_deque.size(); };
    unsigned int  get_max_size()   const{ return deque_max; };
    
    void print_deque_size(){std::cout<<get_deque_size()<<std::endl;}

    publisher pop_message();
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
    void running_thread();
    void stop_broadcasting();
};


}//namespace end

#endif // !SERVER