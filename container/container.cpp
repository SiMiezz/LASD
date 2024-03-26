namespace lasd {

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer<Data>& container) const noexcept{
  if(size == container.Size()){
    for(uint i=0;i<size;i++){
      if(operator[](i) != container(i)){
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
bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& container) const noexcept{
  return !(*this == container);
}

/* ************************************************************************** */

// Specific member functions

template <typename Data>
Data& LinearContainer<Data>::Front() const{
  if(size != 0){
    return operator[](0);
  }
  else{
    throw std::length_error("accesso negato");
  }
}

template <typename Data>
Data& LinearContainer<Data>::Back() const{
  if(size != 0){
    return operator[](size-1);
  }
  else{
    throw std::length_error("accesso negato");
  }
}

/* ************************************************************************** */

// Specific member functions

template <typename Data>
void AuxFoldExists(const Data& dato, const void* val, void* exists)noexcept{
  if(dato == *((Data*) val)){
    *((bool*) exists) = true;
  }
}

template <typename Data>
bool FoldableContainer<Data>::Exists(const Data& dato) const noexcept{
  bool exists = false;
  Fold(&AuxFoldExists<Data>,&dato,&exists);
  return exists;
}

template <typename Data>
void PreOrderMappableContainer<Data>::Map(MapFunctor funct, void* parametro){
  MapPreOrder(funct,parametro);
}

template <typename Data>
void PostOrderMappableContainer<Data>::Map(MapFunctor funct, void* parametro){
  MapPostOrder(funct,parametro);
}

template <typename Data>
void InOrderMappableContainer<Data>::Map(MapFunctor funct, void* parametro){
  MapInOrder(funct,parametro);
}

template <typename Data>
void BreadthMappableContainer<Data>::Map(MapFunctor funct, void* parametro){
  MapBreadth(funct,parametro);
}

template <typename Data>
void PreOrderFoldableContainer<Data>::Fold(FoldFunctor funct, const void* parametro, void* accumulatore)const{
  FoldPreOrder(funct,parametro,accumulatore);
}

template <typename Data>
void PostOrderFoldableContainer<Data>::Fold(FoldFunctor funct, const void* parametro, void* accumulatore)const{
  FoldPostOrder(funct,parametro,accumulatore);
}

template <typename Data>
void InOrderFoldableContainer<Data>::Fold(FoldFunctor funct, const void* parametro, void* accumulatore) const{
  FoldInOrder(funct,parametro,accumulatore);
}

template <typename Data>
void BreadthFoldableContainer<Data>::Fold(FoldFunctor funct, const void* parametro, void* accumulatore) const{
  FoldBreadth(funct,parametro,accumulatore);
}

/* ************************************************************************** */

// Specific member functions
template <typename Data>
void DictionaryContainer<Data>::Insert(const LinearContainer<Data>& container){
  for(uint i=0;i<container.Size();i++){
    Insert(container[i]);
  }
}

template <typename Data>
void DictionaryContainer<Data>::Insert(LinearContainer<Data>&& container){
  for(uint i=0;i<container.Size();i++){
    Insert(std::move(container[i]));
  }
}

template <typename Data>
void DictionaryContainer<Data>::Remove(const LinearContainer<Data>& container){
  for(uint i=0;i<container.Size();i++){
    Remove(container[i]);
  }
}

}
