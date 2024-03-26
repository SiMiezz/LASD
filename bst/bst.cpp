
namespace lasd {

/* ************************************************************************** */

// Specific constructors
template <typename Data>
BST<Data>::BST::BST(const LinearContainer<Data>& container){
    for(uint i=0;i<container.Size();i++){
        Insert(container[i]);
    }
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BST<Data>& BST<Data>::BST::operator=(const BST& tree){
    BinaryTreeLnk<Data>::operator=(tree);
    return *this;
}

// Move assignment
template <typename Data>
BST<Data>& BST<Data>::BST::operator=(BST&& tree) noexcept{
    BinaryTreeLnk<Data>::operator=(std::move(tree));
    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BST<Data>::BST::operator==(const BST& tree) const noexcept{
    if(size == tree.Size()){
        if(size == 0){
            return true;
        }
        BTInOrderIterator<Data> itr1(*this);
        BTInOrderIterator<Data> itr2(tree);

        while(!itr1.Terminated()){
            if(*itr1 != *itr2){
                return false;
            }

            ++itr1;
            ++itr2;
        }
    }
    else{
        return false;
    }

    return true;
}

template <typename Data>
bool BST<Data>::BST::operator!=(const BST& tree) const noexcept{
    return !(*this == tree);
}

/* ************************************************************************ */

// Specific member functions
template <typename Data>
const Data& BST<Data>::BST::Min() const{
    if(size != 0){
        return (FindPointerToMin(root))->key;
    }
    else{
        throw std::length_error("Accesso negato");
    }
}

template <typename Data>
Data BST<Data>::BST::MinNRemove(){
    if(size != 0){
        return DataNDelete(FindPointerToMin(root));
    }
    else{
        throw std::length_error("Accesso negato");
    }
}

template <typename Data>
void BST<Data>::BST::RemoveMin(){
    if(size != 0){
        delete DetachMin(root);
    }
    else{
        throw std::length_error("Accesso negato");
    }
}

template <typename Data>
const Data& BST<Data>::BST::Max() const{
    if(size != 0){
        return (FindPointerToMax(root))->key;
    }
    else{
        throw std::length_error("Accesso negato");
    }
}

template <typename Data>
Data BST<Data>::BST::MaxNRemove(){
    if(size != 0){
        return DataNDelete(FindPointerToMax(root));
    }
    else{
        throw std::length_error("Accesso negato");
    }
}

template <typename Data>
void BST<Data>::BST::RemoveMax(){
    if(size != 0){
        delete DetachMax(root);
    }
    else{
        throw std::length_error("Accesso negato");
    }
}

template <typename Data>
const Data& BST<Data>::BST::Predecessor(const Data& dato) const{
    if(size != 0){
        NodeLnk* const* pred = FindPointerToPredecessor(root,dato);

        if(pred != nullptr){
            return (*pred)->key;
        }
        else{
            throw std::length_error("Accesso negato");
        } 
    }
    else{
        throw std::length_error("Accesso negato");
    }
}

template <typename Data>
Data BST<Data>::BST::PredecessorNRemove(const Data& dato){
    if(size != 0){
        NodeLnk** pred = FindPointerToPredecessor(root,dato);

        if(pred != nullptr){
            return DataNDelete(*pred);
        }
        else{
            throw std::length_error("Accesso negato");
        } 
    }
    else{
        throw std::length_error("Accesso negato");
    }
}

template <typename Data>
void BST<Data>::BST::RemovePredecessor(const Data& dato){
    if(size != 0){
        NodeLnk** pred = FindPointerToPredecessor(root,dato);

        if(pred != nullptr){
            delete Detach(*pred);
        }
    }
}

template <typename Data>
const Data& BST<Data>::BST::Successor(const Data& dato) const{
    if(size != 0){
        NodeLnk* const* succ = FindPointerToSuccessor(root,dato);

        if(succ != nullptr){
            return (*succ)->key;
        }
        else{
            throw std::length_error("Accesso negato");
        }
    }
    else{
        throw std::length_error("Accesso negato");
    }
}

template <typename Data>
Data BST<Data>::BST::SuccessorNRemove(const Data& dato){
    if(size != 0){
        NodeLnk** succ = FindPointerToSuccessor(root,dato);

        if(succ != nullptr){
            return DataNDelete(*succ);
        }
        else{
            throw std::length_error("Accesso negato");
        }
    }
    else{
        throw std::length_error("Accesso negato");
    }
}

template <typename Data>
void BST<Data>::BST::RemoveSuccessor(const Data& dato){
    if(size != 0){
        NodeLnk** succ = FindPointerToSuccessor(root,dato);

        if(succ != nullptr){
            delete Detach(*succ);
        }
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from DictionaryContainer)
template <typename Data>
bool BST<Data>::BST::Insert(const Data& dato){
    NodeLnk*& curr = FindPointerTo(root,dato);

    if(curr == nullptr){
        NodeLnk* nodo = new NodeLnk(dato);
        if(root == nullptr){
            root = nodo;
        }
        else{
            curr = nodo;
        }
        ++size;
        return true;
    }
    else{
        return false;
    }
}

template <typename Data>
bool BST<Data>::BST::Insert(Data&& dato){
    NodeLnk*& curr = FindPointerTo(root,dato);

    if(curr == nullptr){
        NodeLnk* nodo = new NodeLnk(std::move(dato));
        if(root == nullptr){
            root = nodo;
        }
        else{
            curr = nodo;
        }
        ++size;
        return true;
    }
    else{
        return false;
    }
}

template <typename Data>
bool BST<Data>::BST::Remove(const Data& dato){
    NodeLnk*& curr = FindPointerTo(root,dato);

    if(curr != nullptr){
        delete Detach(curr);
        return true;
    }
    else{
        return false;
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from TestableContainer)
template <typename Data>
bool BST<Data>::BST::Exists(const Data& dato) const noexcept{
    NodeLnk* const& curr = FindPointerTo(root,dato);

    if(curr != nullptr){
        return true;
    }
    else{
        return false;
    }
}

/* ************************************************************************ */

// Auxiliary member functions
template <typename Data>
Data BST<Data>::BST::DataNDelete(NodeLnk*& nodo){
    Data dato = nodo->key;

    delete Detach(nodo);
    return dato;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Detach(NodeLnk*& nodo) noexcept{
    if(nodo->HasLeftChild() && nodo->HasRightChild()){
        NodeLnk* min = DetachMin(nodo->right);
        std::swap(nodo->key,min->key);

        return min;
    }
    else{
        if(nodo->HasLeftChild()){
            return Skip2Left(nodo);
        }
        else {
            return Skip2Right(nodo);
        }
    }
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMin(NodeLnk*& nodo) noexcept{
    return Skip2Right(FindPointerToMin(nodo));
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::DetachMax(NodeLnk*& nodo) noexcept{
    return Skip2Left(FindPointerToMax(nodo));
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Left(NodeLnk*& nodo) noexcept{
    NodeLnk* tmp = nullptr;

    if(nodo != nullptr){
        std::swap(tmp,nodo->left);
        std::swap(tmp,nodo);
        --size;
    }
    return tmp;
}

template <typename Data>
typename BST<Data>::NodeLnk* BST<Data>::Skip2Right(NodeLnk*& nodo) noexcept{
    NodeLnk* tmp = nullptr;

    if(nodo != nullptr){
        std::swap(tmp,nodo->right);
        std::swap(tmp,nodo);
        --size;
    }
    return tmp;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMin(NodeLnk*& nodo) noexcept{
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMin(nodo));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMin(NodeLnk* const& nodo) const noexcept{
    NodeLnk* const* pntr = &nodo;
    NodeLnk* curr = nodo;

    if(curr != nullptr){
        while(curr->left != nullptr){
            pntr = &(curr->left);
            curr = curr->left;
        }
    }

    return *pntr;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerToMax(NodeLnk*& nodo) noexcept{
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerToMax(nodo));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerToMax(NodeLnk* const& nodo) const noexcept{
    NodeLnk* const* pntr = &nodo;
    NodeLnk* curr = nodo;

    if(curr != nullptr){
        while(curr->right != nullptr){
            pntr = &(curr->right);
            curr = curr->right;
        }
    }

    return *pntr;
}

template <typename Data>
typename BST<Data>::NodeLnk*& BST<Data>::FindPointerTo(NodeLnk*& nodo, const Data& dato) noexcept{
    return const_cast<NodeLnk*&>(static_cast<const BST<Data>*>(this)->FindPointerTo(nodo,dato));
}

template <typename Data>
typename BST<Data>::NodeLnk* const& BST<Data>::FindPointerTo(NodeLnk* const& nodo, const Data& dato) const noexcept{
    NodeLnk* const* pntr = &nodo;
    NodeLnk* curr = nodo;

    while(curr != nullptr){
        if(curr->key < dato){
            pntr = &(curr->right);
            curr = curr->right;
        }
        else if(curr->key > dato){
            pntr = &(curr->left);
            curr = curr->left;
        }
        else{
            break;
        }
    }
    return *pntr;
}

template <typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToPredecessor(NodeLnk*& nodo, const Data& dato) noexcept{
    return const_cast<NodeLnk**>(static_cast<const BST<Data>*>(this)->FindPointerToPredecessor(nodo,dato));
}

template <typename Data>
typename BST<Data>::NodeLnk* const* BST<Data>::FindPointerToPredecessor(NodeLnk* const& nodo, const Data& dato) const noexcept{
    NodeLnk* const* pntr = &nodo;
    NodeLnk* const* pred = nullptr;

    while(true){
        NodeLnk& curr = **pntr;
        if(curr.key < dato){
            pred = pntr;
            if(curr.right == nullptr){
                return pred;
            }
            else{
                pntr = &(curr.right);
            }
        }
        else{
            if(curr.left == nullptr){
                return pred;
            }
            else{
                if(curr.key > dato){
                    pntr = &(curr.left);
                }
                else{
                    return &FindPointerToMax(curr.left);
                }
            }
        }
    }
}

template <typename Data>
typename BST<Data>::NodeLnk** BST<Data>::FindPointerToSuccessor(NodeLnk*& nodo, const Data& dato) noexcept{
    return const_cast<NodeLnk**>(static_cast<const BST<Data>*>(this)->FindPointerToSuccessor(nodo,dato));
}

template <typename Data>
typename BST<Data>::NodeLnk* const* BST<Data>::FindPointerToSuccessor(NodeLnk* const& nodo, const Data& dato) const noexcept{
    NodeLnk* const* pntr = &nodo;
    NodeLnk* const* pred = nullptr;

    while(true){
        NodeLnk& curr = **pntr;
        if(curr.key > dato){
            pred = pntr;
            if(curr.left == nullptr){
                return pred;
            }
            else{
                pntr = &(curr.left);
            }
        }
        else{
            if(curr.right == nullptr){
                return pred;
            }
            else{
                if(curr.key < dato){
                    pntr = &(curr.right);
                }
                else{
                    return &FindPointerToMin(curr.right);
                }
            }
        }
    }
}

/* ************************************************************************** */

}
