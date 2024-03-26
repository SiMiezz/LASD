
namespace lasd {

/* ************************************************************************** */

// Specific constructors
template<typename Data>
List<Data>::Node::Node(Data&& dato) noexcept{
    std::swap(key,dato);
}

/* ********************************************************************** */

// Move constructor
template<typename Data>
List<Data>::Node::Node(Node&& nodo) noexcept{
    std::swap(key,nodo.key);
    std::swap(next,nodo.next);
}

/* ********************************************************************** */

// Destructor
template<typename Data>
List<Data>::Node::~Node(){
    delete next;
}

/* ********************************************************************** */

// Comparison operators
template<typename Data>
bool List<Data>::Node::operator==(const Node& nodo) const noexcept{
    if(key == nodo.key && next == nodo->next){
        return true;
    }
    else{
        return false;
    }
}

template<typename Data>
bool List<Data>::Node::operator!=(const Node& nodo) const noexcept{
    return!(*this == nodo);
}

/* ************************************************************************** */

// Specific constructor
template<typename Data>
List<Data>::List::List(const LinearContainer<Data>& container){
    for(uint i=0;i<container.Size();i++){
        InsertAtBack(container[i]);
    }
}

/* ************************************************************************ */

// Copy constructor
template<typename Data>
List<Data>::List::List(const List& list){
    Node* curr = list.head;

    while(curr != nullptr){
        this->InsertAtBack(curr->key);
        curr = curr->next;
    }
}

// Move constructor
template<typename Data>
List<Data>::List::List(List&& list) noexcept{
    std::swap(list.head,this->head);
    std::swap(list.tail,this->tail);
    std::swap(list.size,this->size);
}

/* ************************************************************************ */

// Destructor
template<typename Data>
List<Data>::List::~List(){
    tail = nullptr;
    delete tail;
    delete head;
    head = nullptr;
}

/* ************************************************************************ */

// Copy assignment
template<typename Data>
List<Data>& List<Data>::List::operator=(const List& list){
    List<Data>*tmpList = new List<Data>(list);
    
    std::swap(tmpList->head,this->head);
    std::swap(tmpList->tail,this->tail);
    std::swap(tmpList->size,this->size);
    delete tmpList;

    return *this;
}

// Move assignment
template<typename Data>
List<Data>& List<Data>::List::operator=(List&& list) noexcept{
    std::swap(list.head,this->head);
    std::swap(list.tail,this->tail);
    std::swap(list.size,this->size);

    return *this;
}

/* ************************************************************************ */

// Comparison operators
template<typename Data>
bool List<Data>::List::operator==(const List& list) const noexcept{
    if(this->size == list.size){
        Node* curr=head,*curr2=list.head;

        while(curr != nullptr && curr->key == curr2->key){
            curr = curr->next;
            curr2 = curr2->next;
        }

        if(curr != nullptr){
            return false;
        }
        else{
            return true;
        }
    }
    else{
        return false;
    }
}

template<typename Data>
bool List<Data>::List::operator!=(const List& list) const noexcept{
    return !(*this == list);
}

/* ************************************************************************ */

// Specific member functions
template<typename Data>
void List<Data>::List::InsertAtFront(const Data& dato) noexcept{
    Node* newNode = new Node(dato);

    if(this->size == 0){
        head = newNode;
        tail = head;
    }
    else{
        newNode->next = head;
        head = newNode;
    }

    this->size=this->size+1;
}

template<typename Data>
void List<Data>::List::InsertAtFront(Data&& dato) noexcept{
    Node* newNode = new Node(std::move(dato));

    if(this->size == 0){
        head = newNode;
        tail = head;
    }
    else{
        newNode->next = head;
        head = newNode;
    }

    this->size=this->size+1;
}

template<typename Data>
void List<Data>::List::RemoveFromFront(){
    if(this->size != 0){
        Node* tmp = head;
        head = head->next;
        tmp->next = nullptr;
        delete tmp;
        this->size = this->size-1;
    }
    else{
        throw std::length_error("accesso negato");
    }
}

template<typename Data>
Data List<Data>::List::FrontNRemove(){
    if(this->size != 0){
        Node* tmp = head;
        Data dato = head->key;
        head = head->next;
        tmp->next = nullptr;
        delete tmp;
        this->size = this->size-1;

        return dato;
    }
    else{
        throw std::length_error("accesso negato");
    }
}

template<typename Data>
void List<Data>::List::InsertAtBack(const Data& dato) noexcept{
    Node* newNode = new Node(dato);

    if(this->size == 0){
        head = newNode;
        tail = head;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }
    
    this->size=this->size+1;
}

template<typename Data>
void List<Data>::List::InsertAtBack(Data&& dato) noexcept{
    Node* newNode = new Node(std::move(dato));

    if(this->size == 0){
        head = newNode;
        tail = head;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }

    this->size=this->size+1;
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
template<typename Data>
void List<Data>::List::Clear(){
    tail = nullptr;
    delete tail;
    delete head;
    head = nullptr;
    this->size = 0;
}

/* ************************************************************************ */

// Specific member functions (inherited from LinearContainer)
template<typename Data>
Data& List<Data>::List::Front() const{
  if(this->size != 0){
    return head->key;
  }
  else{
    throw std::length_error("accesso negato");
  }
}

template<typename Data>
Data& List<Data>::List::Back() const{
  if(this->size != 0){
    return tail->key;
  }
  else{
    throw std::length_error("accesso negato");
  }
}

template<typename Data>
Data& List<Data>::List::operator[](uint i) const{
  if(i<this->size){
    uint index = 0;
    Node* nodo = head;

    while(index<i){
        nodo = nodo->next;
        index++;
    }

    return nodo->key;
  }
  else{
    throw std::out_of_range("accesso negato");
  }
}

/* ************************************************************************ */

// Specific member functions (inherited from MappableContainer)
template<typename Data>
void List<Data>::List::Map(MapFunctor funct, void* parametro){
    MapPreOrder(funct,parametro,head);
}

// Specific member functions (inherited from PreOrderMappableContainer)
template<typename Data>
void List<Data>::List::MapPreOrder(MapFunctor funct, void* parametro){
    MapPreOrder(funct,parametro,head);
}

// Specific member functions (inherited from PostOrderMappableContainer)
template<typename Data>
void List<Data>::List::MapPostOrder(MapFunctor funct, void* parametro){
    MapPostOrder(funct,parametro,head);
}

/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)
template<typename Data>
void List<Data>::List::Fold(FoldFunctor funct, const void* parametro, void* accumulatore) const{
    FoldPreOrder(funct,parametro,accumulatore,head);
}

// Specific member functions (inherited from PreOrderFoldableContainer)
template<typename Data>
void List<Data>::List::FoldPreOrder(FoldFunctor funct, const void* parametro, void* accumulatore) const{
    FoldPreOrder(funct,parametro,accumulatore,head);
}

// Specific member functions (inherited from PostOrderFoldableContainer)
template<typename Data>
void List<Data>::List::FoldPostOrder(FoldFunctor funct, const void* parametro, void* accumulatore) const{
    FoldPostOrder(funct,parametro,accumulatore,head);
}

/* ************************************************************************ */

// Auxiliary member functions (for PreOrderMappableContainer & PostOrderMappableContainer)
template<typename Data>
void List<Data>::List::MapPreOrder(MapFunctor funct, void* parametro, Node* nodo){
    while(nodo != nullptr){
        funct(nodo->key,parametro);
        nodo = nodo->next;
    }
}

template<typename Data>
void List<Data>::List::MapPostOrder(MapFunctor funct, void* parametro, Node* nodo){
    if(nodo != nullptr){
        MapPostOrder(funct,parametro,nodo->next);
        funct(nodo->key,parametro);
    }
}

/* ************************************************************************ */

// Auxiliary member functions (for PreOrderFoldableContainer & PostOrderFoldableContainer)
template<typename Data>
void List<Data>::List::FoldPreOrder(FoldFunctor funct, const void* parametro, void* accumulatore, Node* nodo) const{
    while(nodo != nullptr){
        funct(nodo->key,parametro,accumulatore);
        nodo = nodo->next;
    }
}

template<typename Data>
void List<Data>::List::FoldPostOrder(FoldFunctor funct, const void* parametro, void* accumulatore, Node* nodo) const{
    if(nodo != nullptr){
        FoldPostOrder(funct,parametro,accumulatore,nodo->next);
        funct(nodo->key,parametro,accumulatore);
    }
}

/* ************************************************************************ */

}
