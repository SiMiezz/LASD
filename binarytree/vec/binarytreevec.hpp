
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public BinaryTree<Data>{

private:

  // ...

protected:

  using BinaryTree<Data>::size;

  struct NodeVec : virtual public BinaryTree<Data>::Node{

  private:

    // ...

  protected:

    using BinaryTree<Data>::Node::key;
    uint index;
    Vector<struct BinaryTreeVec<Data>::NodeVec*>* rif = nullptr;

  public:

    // Specific constructor
    NodeVec(Vector<struct BinaryTreeVec<Data>::NodeVec*>&);

    NodeVec(Vector<struct BinaryTreeVec<Data>::NodeVec*>&,Data&,ulong);

    // Destructor
    virtual ~NodeVec();

    // Copy assignment
    NodeVec& operator=(const NodeVec&) = delete;

    // Move assignment
    NodeVec& operator=(NodeVec&&) noexcept = delete;

    // Specific member functions

    bool HasLeftChild() const noexcept override; // (concrete function should not throw exceptions)
    bool HasRightChild() const noexcept override; // (concrete function should not throw exceptions)

    struct BinaryTree<Data>::Node& LeftChild() override; // (concrete function must throw std::out_of_range when not existent)
    const struct BinaryTree<Data>::Node& LeftChild() const override;
    struct BinaryTree<Data>::Node& RightChild() override; // (concrete function must throw std::out_of_range when not existent)
    const struct BinaryTree<Data>::Node& RightChild() const override;

  };

  Vector<struct BinaryTreeVec<Data>::NodeVec*>* vec = nullptr;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const LinearContainer<Data>&) ; // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec&) ;

  // Move constructor
  BinaryTreeVec(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec() ;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec&) ;

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec&) const noexcept;
  bool operator!=(const BinaryTreeVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  struct BinaryTree<Data>::Node& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthMappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void MapBreadth(MapFunctor, void*) override; // Override BreadthMappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthFoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void FoldBreadth(FoldFunctor, const void*, void*) const override; // Override BreadthFoldableContainer member

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
