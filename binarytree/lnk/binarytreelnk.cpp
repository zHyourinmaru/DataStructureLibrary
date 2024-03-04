
#include "../../vector/vector.hpp"

namespace lasd {

/* ************************************************************************** */

// Specific constructors (NodeLnk)

template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& value) {

    element = value;
    leftChild = nullptr;
    rightChild = nullptr;

}

template<typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data&& value) {

    std::swap(element, value);
    leftChild = nullptr;
    rightChild = nullptr;

}


/* ************************************************************************** */

// Move Assignment

template<typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk&& node) noexcept {

    std::swap(element, node.element);
    std::swap(leftChild, node.leftChild);
    std::swap(rightChild, node.rightChild);

}

/* ************************************************************************** */

// Destructor

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {

    delete leftChild;
    delete rightChild;

}


/* ********************************************************************** */

// Specific member functions

template <typename Data>
Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept {
    
    return element;

}


template <typename Data>
const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept {
    
    return element;

}


template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept {
    
    return (leftChild != nullptr);

}


template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept {
    
    return (rightChild != nullptr);

}


template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
    
    if (leftChild == nullptr)
        throw std::out_of_range("The Left Child does not exists.");

    return *leftChild;

}


template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
    
    if (rightChild == nullptr)
        throw std::out_of_range("The Right Child does not exists.");

    return *rightChild;

}


/* ************************************************************************** */

// Specific constructors (BinaryTreeLnk)

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& structure) {

    if (structure.Empty()) {

        size = 0;
        root = nullptr;

    } else {

        size = structure.Size();
        
        Vector<Data>* vector = new Vector<Data>(structure);

        root = new NodeLnk(structure[0]);

        supportConstructor(vector, root, 0);

        delete vector;

    }

}


/* ************************************************************************ */

// Copy constructor (BinaryTreeLnk)

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& binaryTree) {
    
    size = binaryTree.size;

    root = supportCopyCostructor(binaryTree.root);

}

// Move constructor (BinaryTreeLnk)

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& binaryTree) noexcept {
    
    std::swap(root, binaryTree.root);
    std::swap(size, binaryTree.size);

}


/* ************************************************************************ */

// Destructor (BinaryTreeLnk)

template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk() {
    
    delete root;

}


/* ************************************************************************ */

// Copy assignment (BinaryTreeLnk)

template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& binaryTree) {

    BinaryTreeLnk<Data>* tmpBinaryTree = new BinaryTreeLnk<Data>(binaryTree);
    std::swap(*tmpBinaryTree, *this);

    delete tmpBinaryTree;

    return *this;
}

// Move assignment (BinaryTreeLnk)

template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& binaryTree) noexcept {
    
    std::swap(root, binaryTree.root);
    std::swap(size, binaryTree.size);

    return *this;
}


/* ************************************************************************ */

// Comparison operators (BinaryTreeLnk)

template <typename Data>
bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data>& binaryTree) const noexcept {
    
    return (BinaryTree<Data>::operator==(binaryTree));

}

template <typename Data>
bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data>& binaryTree) const noexcept {
    
    return !(*this == binaryTree);

}


/* ************************************************************************ */

// Specific member functions (inherited from BinaryTree) (BinaryTreeLnk)

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {
    
    if (root == nullptr)
        throw std::length_error("The Binary Tree is empty.");

    return *root;

}


/* ************************************************************************ */

// Specific member functions (inherited from Container) (BinaryTreeLnk)

template <typename Data>
void BinaryTreeLnk<Data>::Clear() {  

    delete root;
    root = nullptr;

    size = 0;
    
}


/* ************************************************************************ */

// Auxiliary member functions (BinaryTreeLnk)

template <typename Data>
void BinaryTreeLnk<Data>::supportConstructor(Vector<Data>* vector, NodeLnk* current, int counter) {
    
    if (current != nullptr && !vector->Empty()) {

        if ((2 * counter + 1) < vector->Size()) {

            current->leftChild = new NodeLnk(vector->operator[](2 * counter + 1));
            supportConstructor(vector, current->leftChild, 2 * counter + 1);

        }

        if ((2 * counter + 2) < vector->Size()) {

            current->rightChild = new NodeLnk(vector->operator[](2 * counter + 2));
            supportConstructor(vector, current->rightChild, 2 * counter + 2);

        }
    }
}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::supportCopyCostructor(NodeLnk* current) {

    if (current != nullptr) {
        
        NodeLnk* tmpNode = new NodeLnk(current->element);

        if (current->leftChild != nullptr) 
            tmpNode->leftChild = supportCopyCostructor(current->leftChild);

        if (current->rightChild != nullptr)
            tmpNode->rightChild = supportCopyCostructor(current->rightChild);

        return tmpNode;

    } else {
        
        return nullptr;

    }
}
}
