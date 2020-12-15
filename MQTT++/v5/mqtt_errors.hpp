// Errores para hacer throw y ver que hice mal

#ifndef ERR
#define ERR


#include <iostream>
#include <string>

namespace mqtt_errors{

//Clase padre
class error: public std::runtime_error
{ 
    public:
    error(std::string msg=""): std::runtime_error(msg){}
};

//Clases hijos
class MQTT_ERR_CONN: public error
{ 
    virtual const char* what() const throw() 
    { return "\nCliente no disponible.\n";  }
};

class MQTT_ERR_DEQUE: public error
{ 
    virtual const char* what() const throw() 
    { return "\nCola de mensajes llena.\n";  }
};

class MQTT_ERR_DEQUE_EMPTY: public error
{ 
    virtual const char* what() const throw() 
    { return "\nCola de mensajes vacía.\n";  }
};

class MQTT_ERR_MESS: public error
{ 
    virtual const char* what() const throw() 
    { return "\nNadie esta suscrito al topic.\n";  }
};

// class MQTT_ERR_CONNACK: public error
// { 
//     virtual const char* what() const throw() 
//     { return "\nError de conexión: El broker no responde.\n";  }
// };

class MQTT_ERR_QOS: public error
{ 
    virtual const char* what() const throw() 
    { return "\nPrioridad desconocido.\n";  }
};

}

#endif // !ERR