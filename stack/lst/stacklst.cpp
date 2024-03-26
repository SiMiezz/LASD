
namespace lasd {

/* ************************************************************************** */

// Copy assignment
template <typename Data>
StackLst<Data>& StackLst<Data>::StackLst::operator=(const StackLst& stack){
    List<Data>::operator=(stack);

    return *this;
}

// Move assignment
template <typename Data>
StackLst<Data>& StackLst<Data>::StackLst::operator=(StackLst&& stack) noexcept{
    List<Data>::operator=(std::move(stack));
    
    return *this;
}

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool StackLst<Data>::StackLst::operator==(const StackLst& stack) const noexcept{
    return List<Data>::operator==(stack);
}

template <typename Data>
bool StackLst<Data>::StackLst::operator!=(const StackLst& stack) const noexcept{
    return !(*this == stack);
}

/* ************************************************************************** */

// Specific member functions (inherited from Stack)
template <typename Data>
const Data& StackLst<Data>::StackLst::Top() const{
    if(size != 0){
        const Data& dato = head->key;

        return dato;
    }
    else{
        throw std::length_error("accesso negato");
    }
}

template <typename Data>
Data& StackLst<Data>::StackLst::Top(){
    if(size != 0){
        return head->key;
    }
    else{
        throw std::length_error("accesso negato");
    }
}

template <typename Data>
void StackLst<Data>::StackLst::Pop(){
    List<Data>::RemoveFromFront();
}

template <typename Data>
Data StackLst<Data>::StackLst::TopNPop(){
    return List<Data>::FrontNRemove();
}

template <typename Data>
void StackLst<Data>::StackLst::Push(const Data& dato){
    List<Data>::InsertAtFront(dato);
}

template <typename Data>
void StackLst<Data>::StackLst::Push(Data&& dato){
    List<Data>::InsertAtFront(std::move(dato));
}

/* ************************************************************************** */

// Specific member functions (inherited from Container)
template <typename Data>
void StackLst<Data>::StackLst::Clear(){
    List<Data>::Clear();
}

/* ************************************************************************** */

}
