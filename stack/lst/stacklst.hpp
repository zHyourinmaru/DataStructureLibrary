
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst :  virtual public Stack<Data>,
                  virtual protected List<Data> {

private:

  // ...

protected:

  using List<Data>::size;
  using List<Data>::head;

public:

  // Default constructor
  StackLst() : List<Data>() {};

  /* ************************************************************************ */

  // Specific constructor
  StackLst(const LinearContainer<Data>& structure) : List<Data>(structure) {}; // A stack obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  StackLst(const StackLst& structure) : List<Data>(structure) {};

  // Move constructor
  StackLst(StackLst&& structure) noexcept : List<Data>(std::move(structure)) {};

  /* ************************************************************************ */

  // Destructor
  virtual ~StackLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackLst& operator=(const StackLst&);

  // Move assignment
  StackLst& operator=(StackLst&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackLst&) const noexcept;
  bool operator!=(const StackLst&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  const Data& Top() const override; // Override Stack member (constant version; must throw std::length_error when empty)
  Data& Top() override; // Override Stack member (must throw std::length_error when empty)
  void Pop() override; // Override Stack member (must throw std::length_error when empty)
  Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)
  void Push(const Data&) override; // Override Stack member (copy of the value)
  void Push(Data&&) override; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
