#ifndef EJER8
#define EJER8 1

#include <iostream>
#include <cassert> //Para el assert

class ejer8 {
    public:
        static const size_t N = 4;

        void *operator new(size_t bytes);
        void operator delete(void *ptr);

        //Constructor Publico
        ejer8() {  std::cout << "Construimos el objeto \"" << getId() << "\" que está en " << this << std::endl;    }

        // Reemplazamos al destructor por esto
        static void destroy(ejer8 *x) { delete x; }

        // Método que retorna cuál de las N instancias posibles es
        ssize_t getId() const;

        static void heapInitializer();
        ssize_t prox_instancia_libre;

    private:
        // Destructor privado para evitar usar el constructor
        //¿Por  que esto funciona? Está idea lo saque de Tapia
        ~ejer8() {std::cout << "Destruimos el \"" << getId() << "\" que está en " << this << std::endl; }

        // Prohibo asignación y construcción copia y move
        ejer8 &operator=(ejer8) = delete;
        ejer8(const ejer8&) = delete;
        ejer8(ejer8&&) = delete;

        // Miembro del objeto. Para hacerlo gordito
        char member[144];

        // Declaración del buffer estático
        static uint8_t heapBuffer[];
        static ssize_t InstanciaLibre;
        static const ssize_t InstanciaNula = -1;

        // Función auxiliar, Tapia lo implementó y yo se lo copié
        static void *new_helper(size_t bytes);

};
namespace {
// Inicialicemos en vector de objetos a un null, 
// Lo hacemos acá para usarlo despueés "X_vect" sin asco.
ejer8 *X_vect = nullptr; 
}

uint8_t ejer8::heapBuffer[ejer8::N * sizeof(ejer8)];
ssize_t ejer8::InstanciaLibre = ejer8::InstanciaNula; // Al inicio el primer objeto disponible está en inválido

void ejer8::heapInitializer()
{   X_vect = (ejer8 *) ejer8::heapBuffer;

    for( size_t i = 0; i < N-1; ++i )
        X_vect[i].prox_instancia_libre = i + 1;

    // El siguiente del último es inválido.
    X_vect[N-1].prox_instancia_libre = InstanciaNula; 

    // EL primer elemento libre es el primero  del vector
    ejer8::InstanciaLibre = 0; 
}

void *ejer8::operator new(size_t bytes)
{
    void *ptr = new_helper(bytes);
    if( ptr == nullptr ) 
    {
        throw std::bad_alloc{};
        };
    return ptr;
}

// Tapia es un crack, super elegante la forma de evitar no tener código repetido
inline void *ejer8::new_helper(size_t bytes)
{
    assert(bytes == sizeof(ejer8));
    ejer8 *dummy = nullptr;
    if( InstanciaLibre != InstanciaNula ) 
    {
        dummy = X_vect + InstanciaLibre;
        InstanciaLibre = dummy->prox_instancia_libre; // La nueva instancia libre
    }
    return dummy;
}

void ejer8::operator delete(void *p)
{
    ejer8 *dummy = (ejer8 *) p;
    dummy->prox_instancia_libre = InstanciaLibre; // La nueva instancia libre
    InstanciaLibre = dummy - X_vect; // "Calculamos" cual es la nueva instancia libre
}

//No lo implemento alla arriba porque uso el namespace X_vect
inline ssize_t ejer8::getId() const { return (ejer8 *) this - X_vect;}

#endif // EJER8