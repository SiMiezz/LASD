
#include <cmath>

namespace lasd {

/* ************************************************************************** */

// Auxiliary member functions
template <typename Data>
void MapInsertOpn(const Data& dato, void* table){
  (*static_cast<HashTableOpnAdr<Data>*>(table)).Insert(dato);
}

template <typename Data>
void AuxFoldEqualsOpn(const Data& dato, const void* table, void* acc)noexcept{
  if(!((*static_cast<const HashTableOpnAdr<Data>*>(table)).Exists(dato))){
    *static_cast<bool*>(acc) = false;
  }
}

// Specific constructors
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr::HashTableOpnAdr(uint newsize){
    if(newsize >= 64){
        uint exp = std::floor(std::log2(newsize))+1;
        newsize = std::pow(2,exp);

        vec.Resize(newsize);
        flag.Resize(newsize);
        m = newsize;
    }
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr::HashTableOpnAdr(const LinearContainer<Data>& container){
    if(container.Size() >= m){
        uint newsize = container.Size();
        uint exp = std::floor(std::log2(newsize))+1;
        newsize = std::pow(2,exp);

        vec.Resize(newsize);
        flag.Resize(newsize);
        m = newsize;
    }

    DictionaryContainer<Data>::Insert(container);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr::HashTableOpnAdr(uint newsize, const LinearContainer<Data>& container){
    if(container.Size() > newsize){
        newsize = container.Size();
    }

    uint exp;
    if(newsize > 64){
        exp = std::floor(std::log2(newsize))+1;
    }
    else{
        exp = 6;
    }
    newsize = std::pow(2,exp);

    vec.Resize(newsize);
    flag.Resize(newsize);
    m = newsize;

    DictionaryContainer<Data>::Insert(container);
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr::HashTableOpnAdr(const HashTableOpnAdr& table){
    vec = Vector<Data>(table.vec);
    flag = Vector<int>(table.flag);
    
    m = table.m;
    a = table.a;
    b = table.b;
    size = table.size;
}

// Move constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr::HashTableOpnAdr(HashTableOpnAdr&& table) noexcept{
    std::swap(vec,table.vec);
    std::swap(flag,table.flag);
    std::swap(size,table.size);
    std::swap(m,table.m);
    std::swap(a,table.a);
    std::swap(b,table.b);
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::HashTableOpnAdr::operator=(const HashTableOpnAdr& table){
    HashTableOpnAdr<Data>* tmp = new HashTableOpnAdr<Data>(table);

    std::swap(*this,*tmp);
    delete tmp;
    return *this;
}

// Move assignment
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::HashTableOpnAdr::operator=(HashTableOpnAdr&& table) noexcept{
    std::swap(vec,table.vec);
    std::swap(flag,table.flag);
    std::swap(size,table.size);
    std::swap(m,table.m);
    std::swap(a,table.a);
    std::swap(b,table.b);

    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool HashTableOpnAdr<Data>::HashTableOpnAdr::operator==(const HashTableOpnAdr& table) const noexcept{
    if(size == table.size){
        bool acc1 = true,acc2 = true;
        Fold(&AuxFoldEqualsOpn<Data>,&table,&acc1);
        if(acc1 == false){
            return false;
        }

        table.Fold(&AuxFoldEqualsOpn<Data>,this,&acc2);
        if(acc2 == false){
            return false;
        }
    }
    else{
        return false;
    }

    return true;
}

template <typename Data>
bool HashTableOpnAdr<Data>::HashTableOpnAdr::operator!=(const HashTableOpnAdr& table) const noexcept{
    return !(*this == table);
}

/* ************************************************************************ */

// Specific member functions (inherited from HashTable)
template <typename Data>
void HashTableOpnAdr<Data>::HashTableOpnAdr::Resize(uint newsize){
    if(newsize > size && newsize > 64){
        uint exp = std::floor(std::log2(newsize))+1;
        newsize = std::pow(2,exp);

        HashTableOpnAdr<Data>* tmp = new HashTableOpnAdr<Data>(newsize);

        Map(&MapInsertOpn<Data>,tmp);

        std::swap(*this,*tmp);
        delete tmp;
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from DictionaryContainer)
template <typename Data>
bool HashTableOpnAdr<Data>::HashTableOpnAdr::Insert(const Data& dato){
    if(!Exists(dato)){
        if(size > m/2){
            Resize(m*2);
        }
        uint index = FindEmpty(dato);
        vec[index] = dato;
        flag[index] = 1;
        ++size;
        return true;
    }
    else{
        return false;
    }    
}

template <typename Data>
bool HashTableOpnAdr<Data>::HashTableOpnAdr::Insert(Data&& dato){
    if(!Exists(dato)){
        if(size > m/2){
            Resize(m*2);
        }
        uint index = FindEmpty(dato);
        vec[index] = dato;
        flag[index] = 1;
        ++size;
        return true;
    }
    else{
        return false;
    }   
}

template <typename Data>
bool HashTableOpnAdr<Data>::HashTableOpnAdr::Remove(const Data& dato){
    if(Exists(dato)){
        flag[Find(dato)] = 2;
        --size;
        return true;
    }
    else{
        return false;
    }
    
}

/* ************************************************************************ */

// Specific member functions (inherited from TestableContainer)
template <typename Data>
bool HashTableOpnAdr<Data>::HashTableOpnAdr::Exists(const Data& dato) const noexcept{
    if(Find(dato) != m+1){
        return true;
    }
    else{
        return false;
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from MappableContainer)
template <typename Data>
void HashTableOpnAdr<Data>::HashTableOpnAdr::Map(MapFunctor funct, void* parametro){
    for(uint i=0;i<m;i++){
        if(flag[i]==1){
            funct(vec[i],parametro);
        }
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)
template <typename Data>
void HashTableOpnAdr<Data>::HashTableOpnAdr::Fold(FoldFunctor funct, const void* parametro, void* accumulatore) const{
    for(uint i=0;i<m;i++){
        if(flag[i]==1){
            funct(vec[i],parametro,accumulatore);
        }
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
template <typename Data>
void HashTableOpnAdr<Data>::HashTableOpnAdr::Clear(){
    HashTableOpnAdr<Data>* tmp = new HashTableOpnAdr<Data>(64);

    std::swap(*this,*tmp);
    delete tmp;
}

/* ************************************************************************ */

// Auxiliary member functions
template <typename Data>
uint HashTableOpnAdr<Data>::HashTableOpnAdr::HashKey(const Data& dato,uint index) const noexcept{
    return((HashTable<Data>::HashKey(dato)+index)%m);
}
template <typename Data>
uint HashTableOpnAdr<Data>::HashTableOpnAdr::Find(const Data& dato) const noexcept{
    uint i = 0;
    while((flag[HashKey(dato,i)] != 1) && i<m){
        i++;
    }

    if(i<m && (vec[HashKey(dato,i)] == dato)){
        return HashKey(dato,i);
    }
    else{
        if(i<m){
            i++;
            while((vec[HashKey(dato,i)] != dato || !(flag[HashKey(dato,i)] != 0 && flag[HashKey(dato,i)] != 2)) && (flag[HashKey(dato,i)] != 0) && i<m){
                i++;
            }
            if(vec[HashKey(dato,i)] == dato){
                if(flag[HashKey(dato,i)] == 1){
                    return HashKey(dato,i);
                }
                else{
                    return m+1;
                }
            }
            else{
                return m+1;
            }
        }
        else{
            return m+1;
        }
    }
}

template <typename Data>
uint HashTableOpnAdr<Data>::HashTableOpnAdr::FindEmpty(const Data& dato) const noexcept{
    uint i = 0;
    while((flag[HashKey(dato,i)] == 1)){
        ++i;
    }

    return HashKey(dato,i);  
}

/* ************************************************************************** */

}
