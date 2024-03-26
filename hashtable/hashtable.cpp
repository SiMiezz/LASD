
namespace lasd {

#include <string>

/* ************************************************************************** */

template <>
class Hash<int>{
public:
    uint operator()(const int& dato) const noexcept{
        return (dato*dato);
    }
};

template <>
class Hash<double>{
public:
    uint operator()(const double& dato) const noexcept{
        int intpart = floor(dato);
        int frazpart = pow(2,24) * (dato - intpart);

        return (intpart * frazpart);
    }
};

template <>
class Hash<std::string>{
public:
    uint operator()(const std::string& dato) const noexcept{
        uint hash = 5381;
        for(uint i = 0;i<dato.length();++i){
            hash = (hash << 5) + dato[i];
        }

        return hash;
    }
};

/* ************************************************************************ */

// Default constructor
template <typename Data>
HashTable<Data>::HashTable::HashTable(){
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dista(1,p-1);
    std::uniform_int_distribution<int> distb(0,p-1);

    a = dista(gen);
    b = distb(gen);
}

/* ************************************************************************ */

  // Auxiliary member functions
template <typename Data>
uint HashTable<Data>::HashTable::HashKey(const Data& k) const noexcept{
    return ((a*(hash(k)) + b)%p)%m;
}

/* ************************************************************************** */

}
