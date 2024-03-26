
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hash {

public:

  uint operator()(const Data&) const noexcept; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public DictionaryContainer<Data>,
                  virtual public MappableContainer<Data>,
                  virtual public FoldableContainer<Data>{ 
                  // Must extend DictionaryContainer<Data>,
                  //             MappableContainer<Data>,
                  //             FoldableContainer<Data>

private:

  // ...

protected:

  using DictionaryContainer<Data>::size;
  uint a,b,m = 64;
  uint const p = 65537;

  Hash<Data> hash{};

public:

  // Default constructor
  HashTable();

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTable& operator=(const HashTable&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable& operator=(HashTable&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable&) const noexcept = delete; // Comparison operators of abstract types should not be possible.
  bool operator!=(const HashTable&) const noexcept = delete; // Comparison operators of abstract types should not be possible.

  /* ************************************************************************ */

  // Specific member function

  virtual void Resize(uint) = 0; // Resize the hashtable to a given size

protected:

  // Auxiliary member functions

  uint HashKey(const Data&) const noexcept;

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
