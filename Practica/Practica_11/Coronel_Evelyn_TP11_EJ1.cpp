#include  <iostream>
#include <vector>
#include <list>

class ShoppingItem
{
private:
    std::string nombre;
    double cantidad;
public:
    ShoppingItem(std::string name, double items=1):nombre(name)
    {cantidad=items;};

    double get_cantidad() const {return cantidad;}
    std::string  get_item() const {return nombre;}
    ~ShoppingItem(){};
};

// Los template template parameters son la cosa mas linda que vi sobre templates <3
// Tengo que especificar que alloque elementos del tipo Shopping Item
// y en el iterator, le digo al compilador que espere el typename, si no le pongo esa palabra
// el programa explota. Todavía no terminé de entender como funciona
// La gracia del typename es que ya no hace falta definir begin() o end() para iterar sobre 
// la lista
template< template<typename, typename=std::allocator<ShoppingItem>> class Container>
class ShoppingList
{
private:
    Container<ShoppingItem> lista;
    typename Container<ShoppingItem>::iterator i;
public:
    ShoppingList(){};
    ~ShoppingList(){};

    double addItem(const std::string &itemName, double cant=1)
    {
        ShoppingItem dummy(itemName, cant);
        lista.push_back(dummy);
        std::cout<<"Agregamos-> Item: "<<itemName<<"\t Cant: "<<cant<<"\n"; 

        double suma=0;

        for (i = lista.begin(); i != lista.end(); ++i)
            suma +=i->get_cantidad();
        return suma;
    };
    
    double getItem(const std::string &itemName)
    {
        if (lista.empty()) {
            std::cout<<"La Lista está vacía.\n";
            return 0;
            }
        else
        {  for (i = lista.begin(); i != lista.end(); ++i)
            {
                if (i->get_item().compare(itemName)==0) 
                {   
                    std::cout<<"Encontramos \""<<itemName<<"\"\n";
                    return i->get_cantidad() ;
                }
            }
            std::cout<<"La Lista no contiene \""<< itemName <<"\".\n";
            return false;
        
        }
    };

    // Esto es muy feo pero ya lo implementé en getItem
    double operator()(const std::string &itemName) {
        return getItem(itemName);

    }
    
    bool removeItem(const std::string &itemName)
    {
        if (lista.empty()) 
        {
            std::cout<<"La lista está vacía.\n";
            return false;
        }
        else
        {  for ( i = lista.begin(); i != lista.end(); ++i)
            {
                if (i->get_item().compare(itemName)==0) 
                {   
                    lista.erase(i);
                    std::cout<<"Removimos \""<<itemName<<"\"\n";
                    return true;
                }
            }
            std::cout<<"La Lista no contiene \""<< itemName <<"\".\n";
            return false;
        
        }
    };
    void print(std::ostream &out)
    {   out<<"____Item_____Cantidad____\n";
        
        for (i = lista.begin(); i != lista.end(); ++i)
            out<<i->get_item()<<"\t\t"<<i->get_cantidad()<<"\n";
        
        out<<"'''''''''''''''''''''''''\n";
    };
};



int main(int argc, char const *argv[])
{
    //ShoppingList<std::list> super;
    ShoppingList<std::vector> super;

    double cantidad = super.addItem("Leche");
    cantidad = super.addItem("Pan", 2);
    cantidad = super.addItem("Papa", 3);
    cantidad = super.addItem("Jamon", 2);

    cantidad -=super("Pan");
    cantidad -=super("Zapallo");

    super.removeItem("Pan");
    super.removeItem("Zapallo");

    super.getItem("Papa");
    super("Pan");
    super("Jamon");

    std::cout<<"Suma: "<<cantidad<<std::endl;

   super.print(std::cout);
    return 0;
}
