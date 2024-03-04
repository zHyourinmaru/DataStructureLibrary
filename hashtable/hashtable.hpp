
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

  ulong operator()(const Data&) const noexcept; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public DictionaryContainer<Data>,
                  virtual public MappableContainer<Data>,
                  virtual public FoldableContainer<Data> { 
                  // Must extend DictionaryContainer<Data>,
                  //             MappableContainer<Data>,
                  //             FoldableContainer<Data>

private:

  // ...

protected:

  using DictionaryContainer<Data>::size;

  ulong tableSize = 128;

  unsigned long long a;
  unsigned long long b;
                                   
  const unsigned long long prime = 1111001101011001111;

  Hash<Data> hashFunction;

  /* ************************************************************************ */

  // Default Constructor
  HashTable();

  /* ************************************************************************ */

  // Copy constructor
  HashTable(const HashTable&);

  // Move constructor
  HashTable(HashTable&&) noexcept;


public:

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTable& operator=(const HashTable&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable&  operator=(HashTable&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable&) const noexcept; // Comparison of abstract binary tree is possible.
  bool operator!=(const HashTable&) const noexcept; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

  // Specific member function

  virtual void Resize(const ulong) = 0; // Resize the hashtable to a given size

protected:

  // Auxiliary member functions

  virtual ulong HashKey(Data) const;

  virtual ulong RoundTableSize(ulong);

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
