
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst :  virtual public Queue<Data>, 
                  virtual protected List<Data> {

private:

  // ...

protected:

  using List<Data>::size;
  using List<Data>::tail;
  using List<Data>::head;

public:

  // Default constructor
  QueueLst() : List<Data>() {};

  /* ************************************************************************ */

  // Specific constructor
  QueueLst(const LinearContainer<Data>& structure) : List<Data>(structure) {}; // A queue obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueLst(const QueueLst& structure) : List<Data>(structure) {};

  // Move constructor
  QueueLst(QueueLst&& structure) noexcept : List<Data>(std::move(structure)) {};


  /* ************************************************************************ */

  // Destructor
  virtual ~QueueLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueLst& operator=(const QueueLst&);

  // Move assignment
  QueueLst& operator=(QueueLst&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueLst&) const noexcept;
  bool operator!=(const QueueLst&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data& Head() const override; // Override Queue member (constant version; must throw std::length_error when empty)
  Data& Head() override; // Override Queue member (must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data&) override; // Override Queue member (copy of the value)
  void Enqueue(Data&&) override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
