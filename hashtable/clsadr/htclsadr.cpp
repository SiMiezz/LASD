
namespace lasd {

/* ************************************************************************** */

// Auxiliary member functions
template <typename Data>
void MapInsert(const Data& dato, void* table){
  (*static_cast<HashTableClsAdr<Data>*>(table)).Insert(dato);
}

template <typename Data>
void AuxFoldEquals(const Data& dato, const void* table, void* acc)noexcept{
  if(!((*static_cast<const HashTableClsAdr<Data>*>(table)).Exists(dato))){
    *static_cast<bool*>(acc) = false;
  }
}

/* ************************************************************************ */

// Specific constructors
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr::HashTableClsAdr(uint newsize){
    vec.Resize(newsize);
    m = newsize;
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr::HashTableClsAdr(const LinearContainer<Data>& container){
    DictionaryContainer<Data>::Insert(container);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr::HashTableClsAdr(uint newsize, const LinearContainer<Data>& container){
    vec.Resize(newsize);
    m = newsize;

    DictionaryContainer<Data>::Insert(container);
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr::HashTableClsAdr(const HashTableClsAdr& table){
    vec = Vector<BST<Data>>(table.vec);

    m = table.m;
    a = table.a;
    b = table.b;
    size = table.size;
}

// Move constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr::HashTableClsAdr(HashTableClsAdr&& table) noexcept{
    std::swap(vec,table.vec);
    std::swap(size,table.size);
    std::swap(m,table.m);
    std::swap(a,table.a);
    std::swap(b,table.b);
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::HashTableClsAdr::operator=(const HashTableClsAdr& table){
    HashTableClsAdr<Data>* tmp = new HashTableClsAdr<Data>(table);

    std::swap(*this,*tmp);
    delete tmp;
    return *this;
}

// Move assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::HashTableClsAdr::operator=(HashTableClsAdr&& table) noexcept{
    std::swap(vec,table.vec);
    std::swap(size,table.size);
    std::swap(m,table.m);
    std::swap(a,table.a);
    std::swap(b,table.b);

    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool HashTableClsAdr<Data>::HashTableClsAdr::operator==(const HashTableClsAdr& table) const noexcept{
    if(size == table.size){
        bool acc1 = true,acc2 = true;
        for(uint i=0;i<m;i++){
            vec[i].Fold(&AuxFoldEquals<Data>,&table,&acc1);
            if(acc1 == false){
                return false;
            }
        }

        for(uint i=0;i<table.m;i++){
            table.vec[i].Fold(&AuxFoldEquals<Data>,this,&acc2);
            if(acc2 == false){
                return false;
            }
        }
    }
    else{
        return false;
    }

    return true;
}

template <typename Data>
bool HashTableClsAdr<Data>::HashTableClsAdr::operator!=(const HashTableClsAdr& table) const noexcept{
    return !(*this == table);
}

/* ************************************************************************ */

// Specific member functions (inherited from HashTable)
template <typename Data>
void HashTableClsAdr<Data>::HashTableClsAdr::Resize(uint newsize){
    HashTableClsAdr<Data>* tmp = new HashTableClsAdr<Data>(newsize);

    Map(&MapInsert<Data>,tmp);

    std::swap(*this,*tmp);
    delete tmp;
}

/* ************************************************************************ */

// Specific member functions (inherited from DictionaryContainer)
template <typename Data>
bool HashTableClsAdr<Data>::HashTableClsAdr::Insert(const Data& dato){
    if(vec[HashKey(dato)].Insert(dato)){
        ++size;
        return true;
    }
    else{
        return false;
    }
}

template <typename Data>
bool HashTableClsAdr<Data>::HashTableClsAdr::Insert(Data&& dato){
    if(vec[HashKey(dato)].Insert(std::move(dato))){
        ++size;
        return true;
    }
    else{
        return false;
    }
}

template <typename Data>
bool HashTableClsAdr<Data>::HashTableClsAdr::Remove(const Data& dato){
    if(vec[HashKey(dato)].Remove(dato)){
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
bool HashTableClsAdr<Data>::HashTableClsAdr::Exists(const Data& dato) const noexcept{
    if(vec[HashKey(dato)].Exists(dato)){
        return true;
    }
    else{
        return false;
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from MappableContainer)
template <typename Data>
void HashTableClsAdr<Data>::HashTableClsAdr::Map(MapFunctor funct, void* parametro){
    for(uint i=0;i<m;i++){
        vec[i].Map(funct,parametro);
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)
template <typename Data>
void HashTableClsAdr<Data>::HashTableClsAdr::Fold(FoldFunctor funct, const void* parametro, void* accumulatore) const{
    for(uint i=0;i<m;i++){
        vec[i].Fold(funct,parametro,accumulatore);
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
template <typename Data>
void HashTableClsAdr<Data>::HashTableClsAdr::Clear(){
    HashTableClsAdr<Data>* tmp = new HashTableClsAdr<Data>(64);

    std::swap(*this,*tmp);
    delete tmp;
}

/* ************************************************************************** */

}
