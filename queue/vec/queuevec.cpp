
namespace lasd {

/* ************************************************************************** */

// // Specific constructor
template <typename Data>
QueueVec<Data>::QueueVec::QueueVec(const LinearContainer<Data>& container) : Vector<Data>(container.Size()+1), tail(size-1){ 
    for(uint i=0;i<container.Size();i++){
        Elements[i]=container[i];
    }
}

// Move constructor
template <typename Data>
QueueVec<Data>::QueueVec::QueueVec(QueueVec&& queue) noexcept : Vector<Data>(std::move(queue)){
    std::swap(head,queue.head);
    std::swap(tail,queue.tail);
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
QueueVec<Data>& QueueVec<Data>::QueueVec::operator=(const QueueVec& queue){
    Vector<Data>::operator=(queue);
    head = queue.head;
    tail = queue.tail;
    return *this;
}

// Move assignment
template <typename Data>
QueueVec<Data>& QueueVec<Data>::QueueVec::operator=(QueueVec&& queue) noexcept{
    Vector<Data>::operator=(std::move(queue));
    std::swap(head,queue.head);
    std::swap(tail,queue.tail);
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool QueueVec<Data>::QueueVec::operator==(const QueueVec& queue) const noexcept{
    if(Size() == queue.Size()){
        uint i = head, j = queue.head;
        while(i != tail){
            if(Elements[i] != queue.Elements[j]){
                return false;
            }

            i = (i+1)%size;
            j = (j+1)%queue.size;
        }
    }
    else{
        return false;
    }

    return true;
}

template <typename Data>
bool QueueVec<Data>::QueueVec::operator!=(const QueueVec& queue) const noexcept{
    return !(*this == queue);
}

/* ************************************************************************ */

// Specific member functions (inherited from Queue)
template <typename Data>
const Data& QueueVec<Data>::QueueVec::Head() const{
    if(!Empty()){
        const Data& dato = Elements[head];

        return dato;
    }
    else{
        throw std::length_error("accesso negato");
    }
}

template <typename Data>
Data& QueueVec<Data>::QueueVec::Head(){
    if(!Empty()){
        return Elements[head];
    }
    else{
        throw std::length_error("accesso negato");
    }
}

template <typename Data>
void QueueVec<Data>::QueueVec::Dequeue(){
    if(!Empty()){
        head = (head+1)%size;
        Reduce();
    }
    else{
        throw std::length_error("accesso negato");
    }
}

template <typename Data>
Data QueueVec<Data>::QueueVec::HeadNDequeue(){
    if(!Empty()){
        Data tmp = Elements[head];
        head = (head+1)%size;
        
        Reduce();

        return tmp;
    }
    else{
        throw std::length_error("accesso negato");
    }
}

template <typename Data>
void QueueVec<Data>::QueueVec::Enqueue(const Data& dato){
    Expand();
    
    Elements[tail] = dato;
    tail = (tail+1)%size;
}

template <typename Data>
void QueueVec<Data>::QueueVec::Enqueue(Data&& dato){
    Expand();
    
    std::swap(Elements[tail],dato);
    tail = (tail+1)%size;
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
template <typename Data>
bool QueueVec<Data>::QueueVec::Empty() const noexcept{
    return(tail == head);
}

template <typename Data>
uint QueueVec<Data>::QueueVec::Size() const noexcept{
    if(tail<head){
        return size-(head-tail);
    }
    else{
        return tail-head;
    }
}

template <typename Data>
void QueueVec<Data>::QueueVec::Clear(){
    Vector<Data>::Resize(1);
    head = 0;
    tail = 0;
}

/* ************************************************************************ */

// Auxiliary member functions
template <typename Data>
void QueueVec<Data>::QueueVec::Expand(){
    if(tail == (head-1)%size){
        QueueVec<Data>* tmpQueue = new QueueVec<Data>();
        tmpQueue->Resize(size*2);

        SwapVectors(*tmpQueue);

        delete tmpQueue;
    }
}

template <typename Data>
void QueueVec<Data>::QueueVec::Reduce(){
    if(Size() <= size/4){
        QueueVec<Data>* tmpQueue = new QueueVec<Data>();
        tmpQueue->Resize(size/2);
        
        SwapVectors(*tmpQueue);

        delete tmpQueue;
    }
}

template <typename Data>
QueueVec<Data>& QueueVec<Data>::QueueVec::SwapVectors(QueueVec& queue){
uint j = head, i = 0;

    while(j!=tail){
        std::swap(queue.Elements[i],Elements[j]);
        j = (j+1)%size;
        i++;
    }
    std::swap(Elements,queue.Elements);
    head = 0;
    tail = i;

    size = queue.size;

    return *this;
}

/* ************************************************************************** */

}
