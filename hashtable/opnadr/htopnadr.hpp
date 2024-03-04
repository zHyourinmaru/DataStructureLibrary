
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"
#include <string.h>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data> { // Must extend HashTable<Data>

private:

  // ...

protected:

  using HashTable<Data>::size;
  using HashTable<Data>::tableSize;
  
  using HashTable<Data>::a;
  using HashTable<Data>::b;
  using HashTable<Data>::prime;
  using HashTable<Data>::hashFunction;

  Vector<Data> vector;

  using HashTable<Data>::HashKey;

  Vector<char> flag = Vector<char>(128);

public:

  // Default constructor
  HashTableOpnAdr();

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(ulong); // A hash table of a given size
  HashTableOpnAdr(LinearContainer<Data>&); // A hash table obtained from a LinearContainer
  HashTableOpnAdr(ulong, LinearContainer<Data>&); // A hash table of a given size obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr&);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableOpnAdr() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr& operator=(const HashTableOpnAdr&);

  // Move assignment
  HashTableOpnAdr& operator=(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr&) const noexcept;
  bool operator!=(const HashTableOpnAdr&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from HashTable)

  virtual void Resize(const ulong); // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  virtual bool Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  virtual bool Insert(Data&&) override; // Override DictionaryContainer member (Move of the value)
  virtual bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  virtual bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void Map(MapFunctor, void*) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void Fold(FoldFunctor, const void*, void*) const override; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

protected:

  // Auxiliary member functions

  virtual ulong HashKey(Data, ulong) const;

  virtual ulong Find(Data, ulong) const;
  virtual ulong FindEmpty(Data) const;

  virtual void Expand();

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
