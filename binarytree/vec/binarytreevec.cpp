
namespace lasd {

/* ************************************************************************** */

// Specific constructor
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Vector<struct BinaryTreeVec<Data>::NodeVec*>& vector){
    rif = &vector;
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Vector<struct BinaryTreeVec<Data>::NodeVec*>& vector,Data& dato,ulong i){
    rif = &vector;
    index = i;
    key = dato;
}

// Destructor
template <typename Data>
BinaryTreeVec<Data>::NodeVec::~NodeVec(){
    if(HasLeftChild()){
        delete &LeftChild();
    }
    
    if(HasRightChild()){
        delete &RightChild();
    }

}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept{
    return(rif!=nullptr && index*2+1<rif->Size() && (*rif)[index*2+1]!=nullptr);
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept{
    return(rif!=nullptr && index*2+2<rif->Size() && (*rif)[index*2+2]!=nullptr);
}

template <typename Data>
struct BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::LeftChild(){
    if(HasLeftChild()){
        return *((*rif)[index*2+1]);
    }
    else{
        throw std::out_of_range("Accesso negato");
    }
}

template <typename Data>
const struct BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::LeftChild() const{
    if(HasLeftChild()){
        return *((*rif)[index*2+1]);
    }
    else{
        throw std::out_of_range("Accesso negato");
    }
}

template <typename Data>
struct BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::RightChild(){
    if(HasRightChild()){
        return *((*rif)[index*2+2]);
    }
    else{
        throw std::out_of_range("Accesso negato");
    }
}

template <typename Data>
const struct BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::RightChild() const{
    if(HasRightChild()){
        return *((*rif)[index*2+2]);
    }
    else{
        throw std::out_of_range("Accesso negato");
    }
}

/* ************************************************************************ */

// Specific constructors
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec::BinaryTreeVec(const LinearContainer<Data>& container){
    vec = new Vector<struct BinaryTreeVec<Data>::NodeVec*>(container.Size());
    size=container.Size();

    for(uint i=0;i<container.Size();i++){
        NodeVec* nodo = new NodeVec(*vec,container[i],i);
        (*vec)[i] = nodo;
    }
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec::BinaryTreeVec(const BinaryTreeVec& tree){
    vec = new Vector<struct BinaryTreeVec<Data>::NodeVec*>(tree.vec->Size());
    size=vec->Size();

    for(uint i=0;i<tree.vec->Size();i++){
        NodeVec* nodo = new NodeVec(*vec,((*(tree.vec))[i])->Element(),i);
        (*vec)[i] = nodo;
    }
}

// Move constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec::BinaryTreeVec(BinaryTreeVec&& tree) noexcept{
    std::swap(vec,tree.vec);
    std::swap(size,tree.size);
}

 /* ************************************************************************ */

// Destructor
template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec(){
    if(size!=0){
        delete &(Root());
    }
    delete vec;
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::BinaryTreeVec::operator=(const BinaryTreeVec& tree){
    BinaryTreeVec<Data>* tmp = new BinaryTreeVec(tree);

    std::swap(*this,*tmp);
    delete tmp;
    return *this;
}

// Move assignment
template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::BinaryTreeVec::operator=(BinaryTreeVec&& tree) noexcept{
    std::swap(vec,tree.vec);
    std::swap(size,tree.size);

    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BinaryTreeVec<Data>::BinaryTreeVec::operator==(const BinaryTreeVec& tree) const noexcept{
    return BinaryTree<Data>::operator==(tree);
}

template <typename Data>
bool BinaryTreeVec<Data>::BinaryTreeVec::operator!=(const BinaryTreeVec& tree) const noexcept{
    return !(this == tree);
}

/* ************************************************************************ */

// Specific member functions (inherited from BinaryTree)
template <typename Data>
struct BinaryTree<Data>::Node& BinaryTreeVec<Data>::Root() const{
    if(size!=0){
        return *((*vec)[0]);
    }
    else{
        throw std::length_error("accesso negato");
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
template <typename Data>
void BinaryTreeVec<Data>::BinaryTreeVec::Clear(){
    if(size!=0){
        delete &(Root());
    }
    if(vec!=nullptr){
        vec->Clear();
    }
    size = 0;
}

/* ************************************************************************ */

// Specific member functions (inherited from BreadthMappableContainer)
template <typename Data>
void BinaryTreeVec<Data>::BinaryTreeVec::MapBreadth(MapFunctor funct, void* parametro){
    for(uint i=0;i<size;i++){
        funct((*vec)[i]->Element(),parametro);
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from BreadthFoldableContainer)
template <typename Data>
void BinaryTreeVec<Data>::BinaryTreeVec::FoldBreadth(FoldFunctor funct, const void* parametro, void* accumulatore) const{
    for(uint i=0;i<size;i++){
        funct((*vec)[i]->Element(),parametro,accumulatore);
    }
}

/* ************************************************************************** */

}
