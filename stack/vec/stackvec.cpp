
namespace lasd {

/* ************************************************************************** */

// Move constructor
template <typename Data>
StackVec<Data>::StackVec::StackVec(StackVec&& stack) noexcept : Vector<Data>(std::move(stack)){
    std::swap(head,stack.head);
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::StackVec::operator=(const StackVec& stack){
    Vector<Data>::operator=(stack);
    head = stack.head;
    return *this;
}

// Move assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::StackVec::operator=(StackVec&& stack) noexcept{
    Vector<Data>::operator=(std::move(stack));
    std::swap(head,stack.head);
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool StackVec<Data>::StackVec::operator==(const StackVec& stack) const noexcept{
    if(head == stack.head){
        for(uint i=0;i<head;i++){
            if(Elements[i] != stack.Elements[i]){
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
bool StackVec<Data>::StackVec::operator!=(const StackVec& stack) const noexcept{
    return !(*this == stack);
}

/* ************************************************************************ */

// Specific member functions (inherited from Stack)
template <typename Data>
const Data& StackVec<Data>::StackVec::Top() const {
    if(!Empty()){
        const Data& dato = Elements[head-1];

        return dato;
    }
    else{
        throw std::length_error("accesso negato");
    }
}

template <typename Data>
Data& StackVec<Data>::StackVec::Top() {
    if(!Empty()){
        return Elements[head-1];
    }
    else{
        throw std::length_error("accesso negato");
    }
}

template <typename Data>
void StackVec<Data>::StackVec::Pop() {
    if(!Empty()){
        head = head-1;
        Reduce();
    }
    else{
        throw std::length_error("accesso negato");
    }
}

template <typename Data>
Data StackVec<Data>::StackVec::TopNPop() {
    if(!Empty()){
        head = head-1;
        Data tmp = Elements[head];
        
        Reduce();

        return tmp;
    }
    else{
        throw std::length_error("accesso negato");
    }
}

template <typename Data>
void StackVec<Data>::StackVec::Push(const Data& dato) {
    Expand();

    Elements[head] = dato;
    head = head+1;
}

template <typename Data>
void StackVec<Data>::StackVec::Push(Data&& dato) {
    Expand();
    
    std::swap(Elements[head],dato);
    head = head+1;
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
template <typename Data>
bool StackVec<Data>::StackVec::Empty() const noexcept{
    return(head==0);
}

template <typename Data>
uint StackVec<Data>::StackVec::Size() const noexcept{
    return head;
}

template <typename Data>
void StackVec<Data>::StackVec::Clear(){
    Vector<Data>::Resize(1);
    head = 0;
}

/* ************************************************************************ */

// Auxiliary member functions
template <typename Data>
void StackVec<Data>::StackVec::Expand(){
    if(Size() == size){
        Vector<Data>::Resize(size*2);
    }
}

template <typename Data>
void StackVec<Data>::StackVec::Reduce(){
    if(head <= size/4){
        Vector<Data>::Resize(size/2);
    }
}

/* ************************************************************************** */

}
