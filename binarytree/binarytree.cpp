
// #include "..."

namespace lasd {

/* ************************************************************************** */

// Comparison operators
template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& nodo) const noexcept{
    if(IsLeaf() && nodo.IsLeaf()){
        return Element()==nodo.Element();
    }
    else{
        if(HasLeftChild() && nodo.HasLeftChild()){
            if(HasRightChild() && nodo.HasRightChild()){
                return (LeftChild()==nodo.LeftChild())&&(RightChild()==nodo.RightChild());
            }
            else if(HasRightChild() || nodo.HasRightChild()){
                return false;
            }
            else{
                return (LeftChild()==nodo.LeftChild());
            }
        }
        else if(HasRightChild() && nodo.HasRightChild()){
            if(HasLeftChild() || nodo.HasLeftChild()){
                return false;
            }
            else{
                return (RightChild()==nodo.RightChild());
            }
        }
        else{
            return false;
        }
    }
}

template <typename Data>
bool BinaryTree<Data>::Node::operator!=(const Node& nodo) const noexcept{
    return!(*this == nodo);
}

/* ********************************************************************** */

// Specific member functions
template <typename Data>
Data& BinaryTree<Data>::Node::Element() noexcept{
    return key;
}

template <typename Data>
const Data& BinaryTree<Data>::Node::Element() const noexcept{
    const Data& dato = key;

    return dato;
}

// Specific member functions
template <typename Data>
bool BinaryTree<Data>::Node::IsLeaf() const noexcept{
    return !(HasLeftChild() || HasRightChild());
}

/* ********************************************************************** */

// Comparison operators
template <typename Data>
bool BinaryTree<Data>::BinaryTree::operator==(const BinaryTree& tree) const noexcept{
    if(size == 0 && tree.size == 0){
        return true;
    }
    else if(size == tree.size){
        return (Root()==tree.Root());
    }
    else{
        return false;
    }
}

template <typename Data>
bool BinaryTree<Data>::BinaryTree::operator!=(const BinaryTree& tree) const noexcept{
    return !(*this == tree);
}

/* ********************************************************************** */

// Specific member functions (inherited from MappableContainer)
template <typename Data>
void BinaryTree<Data>::Map(MapFunctor funct, void* parametro){
    MapBreadth(funct, parametro);
}

/* ************************************************************************ */

// Specific member functions (inherited from FoldableContainer)
template <typename Data>
void BinaryTree<Data>::Fold(FoldFunctor funct, const void* parametro, void* accumulatore) const{
    FoldBreadth(funct,parametro,accumulatore);
}

/* ************************************************************************ */

// Specific member functions (inherited from PreOrderMappableContainer)
template <typename Data>
void BinaryTree<Data>::MapPreOrder(MapFunctor funct, void* parametro){
    if(size!=0){
        MapPreOrder(funct,parametro, Root());
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from PreOrderFoldableContainer)
template <typename Data>
void BinaryTree<Data>::FoldPreOrder(FoldFunctor funct, const void* parametro, void* accumulatore) const{
    if(size!=0){
        FoldPreOrder(funct,parametro,accumulatore, Root());
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from PostOrderMappableContainer)
template <typename Data>
void BinaryTree<Data>::MapPostOrder(MapFunctor funct, void* parametro){
    if(size!=0){
        MapPostOrder(funct,parametro, Root());
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from PostOrderFoldableContainer)
template <typename Data>
void BinaryTree<Data>::FoldPostOrder(FoldFunctor funct, const void* parametro, void* accumulatore) const{
    if(size!=0){
        FoldPostOrder(funct,parametro,accumulatore, Root());
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from InOrderMappableContainer)
template <typename Data>
void BinaryTree<Data>::MapInOrder(MapFunctor funct, void* parametro){
    if(size!=0){
        MapInOrder(funct,parametro, Root());
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from InOrderFoldableContainer)
template <typename Data>
void BinaryTree<Data>::FoldInOrder(FoldFunctor funct, const void* parametro, void* accumulatore) const{
    if(size!=0){
        FoldInOrder(funct,parametro,accumulatore, Root());
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from BreadthMappableContainer)
template <typename Data>
void BinaryTree<Data>::MapBreadth(MapFunctor funct, void* parametro){
    if(size!=0){
        MapBreadth(funct,parametro, Root());
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from BreadthFoldableContainer)
template <typename Data>
void BinaryTree<Data>::FoldBreadth(FoldFunctor funct, const void* parametro, void* accumulatore) const{
    if(size!=0){
        FoldBreadth(funct,parametro,accumulatore, Root());
    }
}

/* ************************************************************************ */

// Auxiliary member functions (for PreOrderMappableContainer)
template <typename Data>
void BinaryTree<Data>::MapPreOrder(MapFunctor funct, void* parametro, Node& nodo){
    funct(nodo.Element(), parametro);

    if(nodo.HasLeftChild()){
        MapPreOrder(funct,parametro,nodo.LeftChild());
    }

    if(nodo.HasRightChild()){
        MapPreOrder(funct,parametro,nodo.RightChild());
    }
}

/* ************************************************************************ */

// Auxiliary member functions (for PreOrderFoldableContainer)
template <typename Data>
void BinaryTree<Data>::FoldPreOrder(FoldFunctor funct, const void* parametro, void* accumulatore, Node& nodo) const{
    funct(nodo.Element(), parametro,accumulatore);

    if(nodo.HasLeftChild()){
        FoldPreOrder(funct,parametro,accumulatore,nodo.LeftChild());
    }
    
    if(nodo.HasRightChild()){
        FoldPreOrder(funct,parametro,accumulatore,nodo.RightChild());
    }
}

/* ************************************************************************ */

// Auxiliary member functions (for PostOrderMappableContainer)
template <typename Data>
void BinaryTree<Data>::MapPostOrder(MapFunctor funct, void* parametro, Node& nodo){
    if(nodo.HasLeftChild()){
        MapPostOrder(funct,parametro,nodo.LeftChild());
    }
    
    if(nodo.HasRightChild()){
        MapPostOrder(funct,parametro,nodo.RightChild());
    }

    funct(nodo.Element(), parametro);
}

/* ************************************************************************ */

// Auxiliary member functions (for PostOrderFoldableContainer)
template <typename Data>
void BinaryTree<Data>::FoldPostOrder(FoldFunctor funct, const void* parametro, void* accumulatore, Node& nodo) const{
    if(nodo.HasLeftChild()){
        FoldPostOrder(funct,parametro,accumulatore,nodo.LeftChild());
    }
    
    if(nodo.HasRightChild()){
        FoldPostOrder(funct,parametro,accumulatore,nodo.RightChild());
    }

    funct(nodo.Element(), parametro,accumulatore);
}

/* ************************************************************************ */

// Auxiliary member functions (for InOrderMappableContainer)
template <typename Data>
void BinaryTree<Data>::MapInOrder(MapFunctor funct, void* parametro, Node& nodo){
    if(nodo.HasLeftChild()){
        MapInOrder(funct,parametro,nodo.LeftChild());
    }

    funct(nodo.Element(), parametro);

    if(nodo.HasRightChild()){
        MapInOrder(funct,parametro,nodo.RightChild());
    }
}

/* ************************************************************************ */

// Auxiliary member functions (for InOrderFoldableContainer)
template <typename Data>
void BinaryTree<Data>::FoldInOrder(FoldFunctor funct, const void* parametro, void* accumulatore, Node& nodo) const{
    if(nodo.HasLeftChild()){
        FoldInOrder(funct,parametro,accumulatore,nodo.LeftChild());
    }

    funct(nodo.Element(), parametro,accumulatore);

    if(nodo.HasRightChild()){
        FoldInOrder(funct,parametro,accumulatore,nodo.RightChild());
    }
}

/* ************************************************************************ */

// Auxiliary member functions (for BreadthMappableContainer)
template <typename Data>
void BinaryTree<Data>::MapBreadth(MapFunctor funct, void* parametro, Node& nodo){
    QueueLst<BinaryTree<Data>::Node*> queue;
    Node* curr;

    queue.Enqueue(&nodo);

    while(!queue.Empty()){
        curr = queue.HeadNDequeue();

        if(curr->HasLeftChild()){
            queue.Enqueue(&(curr->LeftChild()));
        }
        
        if(curr->HasRightChild()){
            queue.Enqueue(&(curr->RightChild()));
        }

        funct(curr->Element(),parametro);
    }
}

/* ************************************************************************ */

// Auxiliary member functions (for BreadthFoldableContainer)
template <typename Data>
void BinaryTree<Data>::FoldBreadth(FoldFunctor funct, const void* parametro, void* accumulatore, Node& nodo) const{
    QueueLst<BinaryTree<Data>::Node*> queue;
    Node* curr;

    queue.Enqueue(&nodo);

    while(!queue.Empty()){
        curr = queue.HeadNDequeue();

        if(curr->HasLeftChild()){
            queue.Enqueue(&(curr->LeftChild()));
        }
        
        if(curr->HasRightChild()){
            queue.Enqueue(&(curr->RightChild()));
        }

        funct(curr->Element(),parametro,accumulatore);
    }
}

/* ************************************************************************ */

// Specific constructors
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator::BTPreOrderIterator(const BinaryTree<Data>& tree){
    root = &(tree.Root());
    curr = root;
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator::BTPreOrderIterator(const BTPreOrderIterator& iterator){
    root = iterator.root;
    curr = iterator.curr;
    stack = iterator.stack;
}

// Move constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator::BTPreOrderIterator(BTPreOrderIterator&& iterator) noexcept{
    std::swap(root,iterator.root);
    std::swap(curr,iterator.curr);
    std::swap(stack,iterator.stack);
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::BTPreOrderIterator::operator=(const BTPreOrderIterator& iterator){
    root = iterator.root;
    curr = iterator.curr;
    stack = iterator.stack;

    return *this;
}

// Move assignment
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::BTPreOrderIterator::operator=(BTPreOrderIterator&& iterator) noexcept{
    std::swap(root,iterator.root);
    std::swap(curr,iterator.curr);
    std::swap(stack,iterator.stack);

    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BTPreOrderIterator<Data>::BTPreOrderIterator::operator==(const BTPreOrderIterator& iterator) const noexcept{
    return(root==iterator.root && curr==iterator.curr && stack==iterator.stack);
}

template <typename Data>
bool BTPreOrderIterator<Data>::BTPreOrderIterator::operator!=(const BTPreOrderIterator& iterator) const noexcept{
    return!(*this == iterator);
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)
template <typename Data>
Data& BTPreOrderIterator<Data>::BTPreOrderIterator::operator*() const{
    if(!Terminated()){
        return curr->Element();
    }
    else{
        throw std::out_of_range("accesso negato");
    }
}

template <typename Data>
bool BTPreOrderIterator<Data>::BTPreOrderIterator::Terminated() const noexcept{
    return(curr==nullptr);
}

/* ************************************************************************ */

// Specific member functions (inherited from ForwardIterator)
template <typename Data>
void BTPreOrderIterator<Data>::BTPreOrderIterator::operator++() {
    if(Terminated()){
        throw std::out_of_range("accesso negato");
    }
    else{
        if(curr->IsLeaf()){
            if(stack.Empty()){
                curr = nullptr;
            }
            else{
                curr = stack.TopNPop();
            }
        }
        else{
            if(curr->HasLeftChild()){
                if(curr->HasRightChild()){
                    stack.Push(&(curr->RightChild()));
                }

                curr = &(curr->LeftChild());
            }
            else{
                curr = &(curr->RightChild());
            }
        }
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from ResettableIterator)
template <typename Data>
void BTPreOrderIterator<Data>::BTPreOrderIterator::Reset() noexcept{
    curr = root;
    stack.Clear();
}

/* ************************************************************************ */

template <typename Data>
struct BinaryTree<Data>::Node* BTPostOrderIterator<Data>::MinLeaf(struct BinaryTree<Data>::Node* nodo) noexcept{
    if(nodo != nullptr){
        if(nodo->IsLeaf()){
            return nodo;
        }
        else{
            if(nodo->HasLeftChild()){
                stack.Push(nodo);
                return MinLeaf(&(nodo->LeftChild()));
            }
            else{
                stack.Push(nodo);
                return MinLeaf(&(nodo->RightChild()));
            }
        }
    }

    return nullptr;
}

// Specific constructors
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator::BTPostOrderIterator(const BinaryTree<Data>& tree){
    root = &(tree.Root());
    curr = MinLeaf(&(tree.Root()));
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator::BTPostOrderIterator(const BTPostOrderIterator& iterator){
    root = iterator.root;
    curr = iterator.curr;
    stack = iterator.stack;
}

// Move constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator::BTPostOrderIterator(BTPostOrderIterator&& iterator) noexcept{
    std::swap(root,iterator.root);
    std::swap(curr,iterator.curr);
    std::swap(stack,iterator.stack);
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::BTPostOrderIterator::operator=(const BTPostOrderIterator& iterator){
    root = iterator.root;
    curr = iterator.curr;
    stack = iterator.stack;

    return *this;
}

// Move assignment
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::BTPostOrderIterator::operator=(BTPostOrderIterator&& iterator) noexcept{
    std::swap(root,iterator.root);
    std::swap(curr,iterator.curr);
    std::swap(stack,iterator.stack);

    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BTPostOrderIterator<Data>::BTPostOrderIterator::operator==(const BTPostOrderIterator& iterator) const noexcept{
    return(root==iterator.root && curr==iterator.curr && stack==iterator.stack);
}

template <typename Data>
bool BTPostOrderIterator<Data>::BTPostOrderIterator::operator!=(const BTPostOrderIterator& iterator) const noexcept{
    return!(*this == iterator);
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)
template <typename Data>
Data& BTPostOrderIterator<Data>::BTPostOrderIterator::operator*() const{
    if(!Terminated()){
        return curr->Element();
    }
    else{
        throw std::out_of_range("accesso negato");
    }
}

template <typename Data>
bool BTPostOrderIterator<Data>::BTPostOrderIterator::Terminated() const noexcept{
    return(curr==nullptr);
}

/* ************************************************************************ */

// Specific member functions (inherited from ForwardIterator)
template <typename Data>
void BTPostOrderIterator<Data>::BTPostOrderIterator::operator++() {
    if(Terminated()){
        throw std::out_of_range("accesso negato");
    }
    else{
        if(stack.Empty()){
            curr = nullptr;
        }
        else{
            if(stack.Top()->HasLeftChild()){
                if(curr == &(stack.Top()->LeftChild())){
                    if(stack.Top()->HasRightChild()){
                        curr = MinLeaf(&(stack.Top()->RightChild()));
                    }
                    else{
                        curr = stack.TopNPop();
                    }
                }
                else{
                    curr = stack.TopNPop();
                }
            }
        }
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from ResettableIterator)
template <typename Data>
void BTPostOrderIterator<Data>::BTPostOrderIterator::Reset() noexcept{
    stack.Clear();
    curr = MinLeaf(root);
}

template <typename Data>
struct BinaryTree<Data>::Node* BTInOrderIterator<Data>::Min(struct BinaryTree<Data>::Node* nodo) noexcept{
    if(nodo != nullptr){
        if(nodo->HasLeftChild()){
            stack.Push(nodo);
            return Min(&(nodo->LeftChild()));
        }
        else{
            return nodo;
        }
    }

    return nullptr;
}
/* ************************************************************************ */

// Specific constructors
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator::BTInOrderIterator(const BinaryTree<Data>& tree){
    root = &(tree.Root());
    curr = Min(&(tree.Root()));
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator::BTInOrderIterator(const BTInOrderIterator& iterator){
    root = iterator.root;
    curr = iterator.curr;
    stack = iterator.stack;
}

// Move constructor
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator::BTInOrderIterator(BTInOrderIterator&& iterator) noexcept{
    std::swap(root,iterator.root);
    std::swap(curr,iterator.curr);
    std::swap(stack,iterator.stack);
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::BTInOrderIterator::operator=(const BTInOrderIterator& iterator){
    root = iterator.root;
    curr = iterator.curr;
    stack = iterator.stack;

    return *this;
}

// Move assignment
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::BTInOrderIterator::operator=(BTInOrderIterator&& iterator) noexcept{
    std::swap(root,iterator.root);
    std::swap(curr,iterator.curr);
    std::swap(stack,iterator.stack);

    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BTInOrderIterator<Data>::BTInOrderIterator::operator==(const BTInOrderIterator& iterator) const noexcept{
    return(root==iterator.root && curr==iterator.curr && stack==iterator.stack);
}

template <typename Data>
bool BTInOrderIterator<Data>::BTInOrderIterator::operator!=(const BTInOrderIterator& iterator) const noexcept{
    return!(*this == iterator);
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)
template <typename Data>
Data& BTInOrderIterator<Data>::BTInOrderIterator::operator*() const{
    if(!Terminated()){
        return curr->Element();
    }
    else{
        throw std::out_of_range("accesso negato");
    }
}

template <typename Data>
bool BTInOrderIterator<Data>::BTInOrderIterator::Terminated() const noexcept{
    return(curr==nullptr);
}

/* ************************************************************************ */

// Specific member functions (inherited from ForwardIterator)
template <typename Data>
void BTInOrderIterator<Data>::BTInOrderIterator::operator++() {
    if(Terminated()){
        throw std::out_of_range("accesso negato");
    }
    else{
        if(!curr->HasRightChild() && stack.Empty()){
            curr = nullptr;
        }
        else{
            if(curr->HasRightChild()){
                curr = Min(&(curr->RightChild()));
            }
            else{
                curr = stack.TopNPop();
            }
        }
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from ResettableIterator)
template <typename Data>
void BTInOrderIterator<Data>::BTInOrderIterator::Reset() noexcept{
    stack.Clear();
    curr = Min(root);
}

/* ************************************************************************ */

// Specific constructors
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator::BTBreadthIterator(const BinaryTree<Data>& tree){
    root = &(tree.Root());
    curr = root;
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator::BTBreadthIterator(const BTBreadthIterator& iterator){
    root = iterator.root;
    curr = iterator.curr;
    queue = iterator.queue;
}

// Move constructor
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator::BTBreadthIterator(BTBreadthIterator&& iterator) noexcept{
    std::swap(root,iterator.root);
    std::swap(curr,iterator.curr);
    std::swap(queue,iterator.queue);
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::BTBreadthIterator::operator=(const BTBreadthIterator& iterator){
    root = iterator.root;
    curr = iterator.curr;
    queue = iterator.queue;

    return *this;
}

// Move assignment
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::BTBreadthIterator::operator=(BTBreadthIterator&& iterator) noexcept{
    std::swap(root,iterator.root);
    std::swap(curr,iterator.curr);
    std::swap(queue,iterator.queue);

    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BTBreadthIterator<Data>::BTBreadthIterator::operator==(const BTBreadthIterator& iterator) const noexcept{
    return(root==iterator.root && curr==iterator.curr && queue==iterator.queue);
}

template <typename Data>
bool BTBreadthIterator<Data>::BTBreadthIterator::operator!=(const BTBreadthIterator& iterator) const noexcept{
    return!(*this == iterator);
}

/* ************************************************************************ */

// Specific member functions (inherited from Iterator)
template <typename Data>
Data& BTBreadthIterator<Data>::BTBreadthIterator::operator*() const{
    if(!Terminated()){
        return curr->Element();
    }
    else{
        throw std::out_of_range("accesso negato");
    }
}

template <typename Data>
bool BTBreadthIterator<Data>::BTBreadthIterator::Terminated() const noexcept{
    return(curr==nullptr);
}

/* ************************************************************************ */

// Specific member functions (inherited from ForwardIterator)
template <typename Data>
void BTBreadthIterator<Data>::BTBreadthIterator::operator++() {
    if(Terminated()){
        throw std::out_of_range("accesso negato");
    }
    else{
        if(curr->IsLeaf() && queue.Empty()){
            curr = nullptr;
        }
        else{
            if(curr->HasLeftChild()){
                queue.Enqueue(&(curr->LeftChild()));
            }
            
            if(curr->HasRightChild()){
                queue.Enqueue(&(curr->RightChild()));
            }
            curr = queue.HeadNDequeue();
        }
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from ResettableIterator)
template <typename Data>
void BTBreadthIterator<Data>::BTBreadthIterator::Reset() noexcept{
    curr = root;
    queue.Clear();
}

/* ************************************************************************** */

}
