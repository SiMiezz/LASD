
#include "../../queue/queue.hpp"
#include "../../queue/lst/queuelst.hpp"

namespace lasd {

/* ************************************************************************** */

// Specific constructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& dato){
    key = dato;
}

// Destructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk(){
    if(HasLeftChild()){
        delete left;
    }
    
    if(HasRightChild()){
        delete right;
    }
}

// Copy assignment
template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk& nodo){
    key = nodo.key;

    if(nodo.left == nullptr){
        delete left;
    }
    else{
        if(left == nullptr){
            left = new NodeLnk();
        }
        *left = *(nodo.left);
    }

    if(nodo.right == nullptr){
        delete right;
    }
    else{
        if(right == nullptr){
            right = new NodeLnk();
        }
        *right = *(nodo.right);
    }

    return *this;
}

// Move assignment
template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk&& nodo) noexcept{
    std::swap(key,nodo.key);
    std::swap(left,nodo.left);
    std::swap(right,nodo.right);

    return *this;
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept{
    if(left != nullptr){
        return true;
    }
    else{
        return false;
    }
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept{
    if(right != nullptr){
        return true;
    }
    else{
        return false;
    }
}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild(){
    if(HasLeftChild()){
        return *left;
    }
    else{
        throw std::out_of_range("Accesso negato");
    }
}

template <typename Data>
const struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const{
    if(HasLeftChild()){
        return *left;
    }
    else{
        throw std::out_of_range("Accesso negato");
    }
}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild(){
    if(HasRightChild()){
        return *right;
    }
    else{
        throw std::out_of_range("Accesso negato");
    }
}

template <typename Data>
const struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const{
    if(HasRightChild()){
        return *right;
    }
    else{
        throw std::out_of_range("Accesso negato");
    }
}

/* ************************************************************************ */

// Specific constructors
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk::BinaryTreeLnk(const LinearContainer<Data>& container){
    QueueLst<BinaryTreeLnk<Data>::NodeLnk*> queue;

    if(!container.Empty()){
        root = new NodeLnk();
        queue.Enqueue(root);
    }

    for(uint i=0;i<container.Size();i++){
        NodeLnk* curr = queue.HeadNDequeue();
        curr->Element() = container[i];

        if(2*i+1<container.Size()){
            curr->left = new NodeLnk();
            queue.Enqueue(curr->left);
        }
        
        if(2*(i+1)<container.Size()){
            curr->right = new NodeLnk();
            queue.Enqueue(curr->right);
        }
    }

    size = container.Size();
}

/* ************************************************************************ */

// Copy constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk::BinaryTreeLnk(const BinaryTreeLnk& tree){
    if(tree.size!=0){
        root = new NodeLnk();
        *root = *(tree.root);
        size = tree.size;
    }
}

// Move constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk::BinaryTreeLnk(BinaryTreeLnk&& tree) noexcept{
    std::swap(tree.root,root);
    std::swap(tree.size,size);
}

/* ************************************************************************ */

// Destructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk::~BinaryTreeLnk(){
    delete root;
}

/* ************************************************************************ */

// Copy assignment
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::BinaryTreeLnk::operator=(const BinaryTreeLnk& tree){
    Clear();
    if(tree.size!=0){
        root = new NodeLnk();
        *root = *(tree.root);
        size = tree.size;
    }

    return *this;
}

// Move assignment
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::BinaryTreeLnk::operator=(BinaryTreeLnk&& tree) noexcept{
    std::swap(tree.root,root);
    std::swap(tree.size,size);

    return *this;
}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool BinaryTreeLnk<Data>::BinaryTreeLnk::operator==(const BinaryTreeLnk& tree) const noexcept{
    return BinaryTree<Data>::operator==(tree);
}

template <typename Data>
bool BinaryTreeLnk<Data>::BinaryTreeLnk::operator!=(const BinaryTreeLnk& tree) const noexcept{
    return!(*this == tree);
}

/* ************************************************************************ */

// Specific member functions (inherited from BinaryTree)
template <typename Data>
struct BinaryTree<Data>::Node& BinaryTreeLnk<Data>::Root() const {
    if(size != 0){
        return *root;
    }
    else{
        throw std::length_error("Accesso negato");
    }
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)
template <typename Data>
void BinaryTreeLnk<Data>::BinaryTreeLnk::Clear() {
    delete root;
    root = nullptr;
    size = 0;
}

/* ************************************************************************** */

}
