#if !defined(MQTT)  
#define MQTT

#include <iostream>
#include <string>

namespace mqtt{

//Variables para errores y comunicacion 

const short CONNECT = 1; //Pedir conectarse
const short CONNACK = 2; //Respuesta del broker

const short PUBLISH = 3; //Pedir publicar  
const short PUBACK  = 4; //Respuesta del broker

const short SUBSCRIBE = 8; //Pedir subscripcion
const short SUBACK = 9; // Respuesta del broker

const short UNSUBSCRIBE = 10; //Pedir unsubscribe
const short UNSUBACK = 11;  //Respuesta del broker

const short MQTT_MESS_SUCCESS=15;
const short MQTT_MESS_N0_SUCCESS=16;
 
// Para simular el prendido y apagado
const bool ON=true;
const bool OFF=false;

// Para indicar que esta conectado si el broker/cliente pregunta
const bool CONNECTED=true; 
// Para indicar que esta desconectado si el broker/cliente pregunta
const bool DISCONNECTED=false;

// Para indicar la calidad de servicio
const short NORMAL=0;
const short HIGH=1;


}
#endif // MQTT
