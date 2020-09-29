#include <iostream>
#include <vector>

template<typename K, typename V>
class pair_feo
{
private:
    K key;
    V value;
public:
    pair_feo(){};
    pair_feo(K llave, V valor):key(llave), value(valor){}
    K getter_key() const{return key;};
    void setter_value(V valor) { value =  valor;};
    V getter_value(){ return value;};
    ~pair_feo(){};
};

template<typename K, typename V>
void print_sum( K llave, V valor)
{
    static  std::vector<pair_feo<K,V>> vec;
    

        for (size_t i = 0; i < vec.size(); i++)
        {   
            std::cout<<i<<"\t"<<vec[i].getter_key()<<"\t"<<vec[i].getter_value()<<"\n";
            try
            {
                if(vec[i].getter_key()==llave)
                    {
                        vec[i].setter_value(vec[i].getter_value() + valor);
                        std::cout<<"pepe";
                        break;
                    }
                
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                continue;
            } 
        }
    vec.push_back(pair_feo<K,V>(llave, valor));   
}


int main(int argc, char const *argv[])
{
    print_sum<char, int>('c', 1);

    return 0;
}
