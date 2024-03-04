
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../bst/bst.hpp"
#include "../../binarytree/binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableClsAdr : virtual public HashTable<Data> { // Must extend HashTable<Data>

private:

  // ...

protected:

  using HashTable<Data>::size;
  using HashTable<Data>::tableSize;
  
  using HashTable<Data>::a;
  using HashTable<Data>::b;
  using HashTable<Data>::prime;
  using HashTable<Data>::hashFunction;

  Vector<BST<Data>> vector;

  using HashTable<Data>::HashKey;

public:

  // Default constructor
  HashTableClsAdr();

  /* ************************************************************************ */

  // Specific constructors
  HashTableClsAdr(ulong); // A hash table of a given size
  HashTableClsAdr(LinearContainer<Data>&); // A hash table obtained from a LinearContainer
  HashTableClsAdr(ulong, LinearContainer<Data>&); // A hash table of a given size obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableClsAdr(const HashTableClsAdr&);

  // Move constructor
  HashTableClsAdr(HashTableClsAdr&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableClsAdr() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTableClsAdr& operator=(const HashTableClsAdr&);

  // Move assignment
  HashTableClsAdr& operator=(HashTableClsAdr&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableClsAdr&) const noexcept;
  bool operator!=(const HashTableClsAdr&) const noexcept;

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

  /* ************************************************************************ */

};

/* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
