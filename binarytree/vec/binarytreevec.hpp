
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public BinaryTree<Data> {
                      // Must extend BinaryTree<Data>

private:

  // ...

protected:

  using BinaryTree<Data>::size;

  // ...

  struct NodeVec : virtual public BinaryTree<Data>::Node { // Must extend Node

  private:

    // ...

  protected:

    // ...

  public:

    Vector<NodeVec*>* nodeVector = nullptr;

    Data element;
    ulong index;


    /* ************************************************************************ */

    // Default constructor
    NodeVec() = default;

    /* ************************************************************************ */

    // Specific constructors
    NodeVec(Data&, ulong, Vector<NodeVec*>*);
  
    /* ************************************************************************ */

    // Destructor
    virtual ~NodeVec() = default;

    /* ************************************************************************ */

    // Specific member functions

    Data& Element() noexcept override; // Mutable access to the element (concrete function should not throw exceptions)
    const Data& Element() const noexcept override; // Immutable access to the element (concrete function should not throw exceptions)

    bool HasLeftChild() const noexcept override; // (concrete function should not throw exceptions)
    bool HasRightChild() const noexcept override; // (concrete function should not throw exceptions)
    
    NodeVec& LeftChild() const override; // (concrete function must throw std::out_of_range when not existent)
    NodeVec& RightChild() const override; // (concrete function must throw std::out_of_range when not existent)

  };

  Vector<NodeVec*>* btVector = nullptr;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec<Data>& operator=(const BinaryTreeVec<Data>&);

  // Move assignment
  BinaryTreeVec<Data>& operator=(BinaryTreeVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec<Data>&) const noexcept;
  bool operator!=(const BinaryTreeVec<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  NodeVec& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

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

  void FoldBreadth(const FoldFunctor, const void*, void*) const override; // Override BreadthFoldableContainer member

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
