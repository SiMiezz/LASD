
namespace lasd {

/* ************************************************************************** */

// Specific constructors
template<typename Data>
Vector<Data>::Vector(const uint resize){
  Elements = new Data[resize];
  size = resize;
}

template<typename Data>
Vector<Data>::Vector(const LinearContainer<Data>& container){
  size = container.Size();
  Elements = new Data[size];

  for(uint i=0;i<size;i++){
    Elements[i] = container[i];
  }
}

// Copy constructor
template<typename Data>
Vector<Data>::Vector(const Vector<Data>& array){
  Elements = new Data[array.size];

  std::copy(array.Elements,array.Elements + array.size,Elements);
  size = array.size;
}

// Move constructor
template<typename Data>
Vector<Data>::Vector(Vector<Data>&& array) noexcept{

  std::swap(Elements,array.Elements);
  std::swap(size,array.size);
}

/* ************************************************************************** */

// Destructor
template<typename Data>
Vector<Data>::~Vector(){
  delete[]Elements;
}

/* ************************************************************************** */

// Copy assignment
template<typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector<Data>& array){
Vector<Data>*tmpArray = new Vector<Data>(array);

  std::swap(*tmpArray,*this);
  delete tmpArray;

return *this;
}

// Move assignment
template<typename Data>
Vector<Data>& Vector<Data>::operator=(Vector<Data>&& array) noexcept{

std::swap(Elements,array.Elements);
std::swap(size,array.size);
return *this;
}

/* ************************************************************************** */

// Comparison operators
template<typename Data>
bool Vector<Data>::operator==(const Vector<Data>& array) const noexcept{
  if(size == array.size){
    for(uint i=0;i<size;i++){
      if(Elements[i] != array.Elements[i]){
        return false;
      }
    }
  }
  else{
    return false;
  }

  return true;
}

template<typename Data>
bool Vector<Data>::operator!=(const Vector<Data>& array) const noexcept{
  return !(*this == array);
}

/* ************************************************************************** */

// Resize the vector to a given size
template<typename Data>
void Vector<Data>::Resize(const uint resize){
  if(resize == 0){
    Clear();
  }
  else if(size != resize){
    Data* tmpArray = new Data[resize] {};
    uint newsize;

    if(size < resize){
      newsize = size;
    }
    else{
      newsize = resize;
    }

    for(uint i=0;i<newsize;++i){
      std::swap(Elements[i],tmpArray[i]);
    }
    std::swap(Elements,tmpArray);

    size = resize;
    delete[]tmpArray;
  }
}

// Override Container member
template<typename Data>
void Vector<Data>::Clear(){
  delete[] Elements;
  Elements = nullptr;
  size = 0;
} 

/* ************************************************************************ */

// Override LinearContainer member
template<typename Data>
Data& Vector<Data>::Front() const{
  if(size != 0){
    return Elements[0];
  }
  else{
    throw std::length_error("accesso negato");
  }
}

// Override LinearContainer member
template<typename Data>
Data& Vector<Data>::Back() const{
  if(size != 0){
    return Elements[size-1];
  }
  else{
    throw std::length_error("accesso negato");
  }
}

// Override LinearContainer member
template<typename Data>
Data& Vector<Data>::operator[](uint i) const{
  if(i<size){
    return Elements[i];
  }
  else{
    throw std::out_of_range("accesso negato");
  }
}

/* ************************************************************************ */

// Override MappableContainer member
template<typename Data>
void Vector<Data>::Map(MapFunctor funct, void* parametro){
  MapPreOrder(funct,parametro);
} 

// Override PreOrderMappableContainer member
template<typename Data>
void Vector<Data>::MapPreOrder(MapFunctor funct, void* parametro){
  for(uint i=0;i<size;++i){
    funct(Elements[i],parametro);
  }
}

// Override PostOrderMappableContainer member
template<typename Data>
void Vector<Data>::MapPostOrder(MapFunctor funct, void* parametro){
uint i=size;
while(i>0){
  funct(Elements[--i],parametro);  
}
}

// Override FoldableContainer member
template<typename Data>
void Vector<Data>::Fold(FoldFunctor funct, const void* parametro, void* accumulatore) const{
  FoldPreOrder(funct,parametro,accumulatore);
}

// Override FoldableContainer member
template<typename Data>
void Vector<Data>::FoldPreOrder(FoldFunctor funct, const void* parametro, void* accumulatore) const{
  for(uint i=0;i<size;++i){
    funct(Elements[i],parametro,accumulatore);
  }
}

// Override FoldableContainer member
template<typename Data>
void Vector<Data>::FoldPostOrder(FoldFunctor funct, const void* parametro, void* accumulatore) const{
uint i=size;
while(i>0){
  funct(Elements[--i],parametro,accumulatore);  
}
}

/* ************************************************************************ */

}