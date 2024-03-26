
namespace lasd {

/* ************************************************************************** */

// Copy assignment
template <typename Data>
QueueLst<Data>& QueueLst<Data>::QueueLst::operator=(const QueueLst& queue){
    List<Data>::operator=(queue);

    return *this;
}

// Move assignment
template <typename Data>
QueueLst<Data>& QueueLst<Data>::QueueLst::operator=(QueueLst&& queue) noexcept{
    List<Data>::operator=(std::move(queue));
    
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool QueueLst<Data>::QueueLst::operator==(const QueueLst& queue) const noexcept{
    return List<Data>::operator==(queue);
}

template <typename Data>
bool QueueLst<Data>::QueueLst::operator!=(const QueueLst& queue) const noexcept{
    return !(*this == queue);
}

/* ************************************************************************ */

// Specific member functions (inherited from Queue)
template <typename Data>
const Data& QueueLst<Data>::QueueLst::Head() const{
    if(size != 0){
        const Data& dato = head->key;

        return dato;
    }
    else{
        throw std::length_error("accesso negato");
    }
}

template <typename Data>
Data& QueueLst<Data>::QueueLst::Head(){
    if(size != 0){
        return head->key;
    }
    else{
        throw std::length_error("accesso negato");
    }
}

template <typename Data>
void QueueLst<Data>::QueueLst::Dequeue(){
    List<Data>::RemoveFromFront();
}

template <typename Data>
Data QueueLst<Data>::QueueLst::HeadNDequeue(){
    return List<Data>::FrontNRemove();
}

template <typename Data>
void QueueLst<Data>::QueueLst::Enqueue(const Data& dato){
    List<Data>::InsertAtBack(dato);
}

template <typename Data>
void QueueLst<Data>::QueueLst::Enqueue(Data&& dato){
    List<Data>::InsertAtBack(std::move(dato));
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
template <typename Data>
void QueueLst<Data>::QueueLst::Clear(){
    List<Data>::Clear();
}

/* ************************************************************************** */

}
