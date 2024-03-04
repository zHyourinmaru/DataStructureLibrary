
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec :  virtual public Queue<Data>,
                  virtual protected Vector<Data> {

private:

  // ...

protected:

  using Vector<Data>::size;
  using Vector<Data>::Array;

  ulong head = 0;
  ulong tail = 0;

public:

  // Default constructor
  QueueVec() : Vector<Data>(1) {};

  /* ************************************************************************ */

  // Specific constructor
  QueueVec(const LinearContainer<Data>& structure); // A queue obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueVec(const QueueVec& structure) : Vector<Data>(structure), head(structure.head), tail(structure.tail) {};

  // Move constructor
  QueueVec(QueueVec&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueVec& operator=(const QueueVec&);

  // Move assignment
  QueueVec& operator=(QueueVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueVec&) const noexcept;
  bool operator!=(const QueueVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data& Head() const override; // Override Queue member (constant version; must throw std::length_error when empty)
  Data& Head() override; // Override Queue member (must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data& value) override; // Override Queue member (copy of the value)
  void Enqueue(Data&& value) override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override; // Override Container member

  inline ulong Size() const noexcept override; // Override Container member

  void Clear() override; // Override Container member

protected:

  // Auxiliary member functions

  void Expand();
  void Reduce();
  void SwapVectors(ulong);

};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
